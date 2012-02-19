/*
 * Machine::.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Machine.h"

#include "NodeWalker.h"
#include "object/Object.h"
#include "object/Heap.h"
#include "../tree/Node.h"
#include <tr1/memory>
using namespace tree;
using std::tr1::shared_ptr;
namespace machine{

static const std::string TAG("Machine");

Machine::Machine(logging::Logger& log)
:heap()
,log(log)
{
	Object* const topLevel(heap.newObject());
	selfStack.push(topLevel);
	this->enterLocal(heap.newUndefinedObject(), topLevel);
}

Machine::~Machine()
{
}

void Machine::walkIn(){
}

void Machine::walkOut(){
}

void Machine::pushResult(Object* obj){
	resultStack.push(obj);
}
Object* Machine::getArgument(){
	return argStack.top();
}
Object* Machine::getSelf(){
	return selfStack.top();
}
Object* Machine::getTopLevel(){
	return selfStack.bottom();
}
Object* Machine::getLocal()
{
	return scopeStack.top();
}
void Machine::enterLocal(Object* parent, Object* local)
{
	local->setSlot("$$parent", parent);
	scopeStack.push(local);
}
void Machine::endLocal(Object* local)
{
	if(scopeStack.top() != local){
		this->log.e(TAG, 0, "[BUG] calling \"end local\" was forgotten!");
	}
	scopeStack.pop();
}

Object* Machine::resolveScope(const std::string& name, const bool isLocal)
{
	if(name.compare("self") == 0){
		this->log.t(TAG, 0, "Scope Resolved: self");
		return getSelf();
	}else if(name.compare("local") == 0){
		this->log.t(TAG, 0, "Scope Resolved: \"local\"");
		return getLocal();
	}else if(isLocal){
		for(Object* obj = getLocal();!obj->isUndefined();obj=obj->getSlot("$$parent")){
			Object* const slot = obj->getSlot(name);
			if(!slot->isUndefined()){
				this->log.t(TAG, 0, "Scope Resolved: %s in %s", name.c_str(), obj->toStringObject()->toString().c_str());
				return obj;
			}
		}
		this->log.t(TAG, 0, "%s not found.", name.c_str());
		return getLocal();
	}else{
		this->log.t(TAG, 0, "Scope resolved: %s in TopLevelObject", name.c_str());
		return getTopLevel();
	}
}

Object* Machine::eval(const Node * node, Object* const arg){
	if(arg){
		argStack.push(arg);
	}else{
		argStack.push(heap.newUndefinedObject());
	}
	node->accept(*this);
	argStack.pop();
	return resultStack.pop();
}
Object* Machine::send(Object* const self, const std::string& message, Object* const arg){
	if(arg){
		argStack.push(arg);
	}else{
		argStack.push(heap.newUndefinedObject());
	}
	if(self){
		selfStack.push(self);
		self->getSlot(message)->eval(*this);
		selfStack.pop();
	}else{
		self->getSlot(message)->eval(*this);
	}
	argStack.pop();
	return resultStack.pop();
}

void Machine::walkImpl(const BoolLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating Boolean node: %s", node.getLiteral() ? "true" : "false");
	pushResult(heap.newBooleanObject(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating Numeric node: %f", node.getLiteral());
	pushResult(heap.newNumericObject(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating Numeric node: %s", node.getLiteral().c_str());
	pushResult(heap.newStringObject(node.getLiteral()));
}
void Machine::walkImpl(const AssignNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating assign node");
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
	if(invokeNode){
		this->log.t(TAG, &invokeNode->location(), "Evaluating assign node with invoke node.");
		Object* destObj = 0;
		Object* const rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName(), node.isLocal());
		}
		StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());
		Object* const arg = heap.newArray(nameObj,rhsObj, 0);

		send(destObj, "setSlot", arg);
		pushResult(rhsObj);
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating assign node with index access node.");
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());
		Object* const rhsObj = eval(node.getRightNode());

		send(destObj, "indexSet", heap.newArray(idxObj->index(0), rhsObj, 0));
		pushResult(rhsObj);
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating op assign node: %s", node.getOp().c_str());
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
	if(invokeNode){
		this->log.t(TAG, &invokeNode->location(), "Evaluating op assign node with invoke node.");
			Object* destObj = 0;
		Object* const rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName(), true);
		}
		StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		Object* const operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		Object* const result = send(operandObj, node.getOp(), heap.newArray(rhsObj, 0));

		send(destObj, "setSlot", heap.newArray(nameObj, result, 0));
		pushResult(result);
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating op assign node with index access node.");
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());
		Object* const rhsObj = eval(node.getRightNode());

		Object* const operandObj = send(destObj, "index", idxObj);
		Object* const result = send(operandObj, node.getOp(), heap.newArray(rhsObj, 0));

		send(destObj, "indexSet", heap.newArray(idxObj->index(0), result, 0));
		pushResult(result);
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid op assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const IndexAcessNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating index access node.");
	Object* const destObj = eval(node.getExprNode());
	pushResult(send(destObj, "index", heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const BindNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating bind node.");
	pushResult(eval(node.getExprNode(), heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const PostOpNode & node)
{
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getExprNode());
	if(invokeNode){
		this->log.t(TAG, &node.location(), "Evaluating post op node with invoke node: %s", node.getOp().c_str());
		Object* destObj = 0;
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName(), true);
		}
		StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		Object* operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		Object* const result = send(operandObj, node.getOp());

		send(destObj, "setSlot", heap.newArray(nameObj, result, 0));
		pushResult(operandObj);
	}else if(idxNode){
		this->log.t(TAG, &node.location(), "Evaluating post op node with index access node: %s", node.getOp().c_str());
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());

		Object* const operandObj = send(destObj, "index", idxObj);
		Object* const result = send(operandObj, node.getOp());

		send(destObj, "indexSet", heap.newArray(idxObj->index(0), result, 0));

		pushResult(operandObj);
	}else{
		this->log.w(TAG, &node.location(), "Invalid post op node.");
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const PreOpNode & node)
{
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getExprNode());
	if(invokeNode){
		this->log.t(TAG, &node.location(), "Evaluating pre op node with invoke node: %s", node.getOp().c_str());
		Object* destObj = 0;
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName(), true);
		}
		StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		Object* operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		Object* const result = send(operandObj, node.getOp());
		send(destObj, "setSlot", heap.newArray(nameObj, result, 0));

		pushResult(result);
	}else if(idxNode){
		this->log.t(TAG, &node.location(), "Evaluating pre op node with index access node: %s", node.getOp().c_str());
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());

		Object* const operandObj = send(destObj, "index", idxObj);
		Object* const result = send(operandObj, node.getOp());

		send(destObj, "indexSet", heap.newArray(idxObj->index(0), result, 0));

		pushResult(operandObj);
	}else{
		this->log.w(TAG, &node.location(), "Invalid pre op node.");
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const BinOpNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating bin op node: %s", node.getOp().c_str());
	Object* const leftObj = eval(node.getLeftNode());
	Object* const rightObj = eval(node.getRightNode());
	pushResult( send(leftObj, node.getOp(), heap.newArray(rightObj, 0)) );
}
void Machine::walkImpl(const ObjectNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating object node.");
	Object* const obj = heap.newObject();

	const size_t argc = node.size();
	for(size_t i=0;i<argc;++i){
		obj->push(eval(node.index(i)));
	}

	std::vector<std::string> args = node.getSlotNames();
	for(std::vector<std::string>::const_iterator it = args.begin();it!=args.end();++it){
		obj->setSlot(*it, eval(node.getSlot(*it)));
	}
	pushResult(obj);
}
void Machine::walkImpl(const InvokeNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating invoke node.");
	if(node.getExprNode()){
		Object* const destObj = eval(node.getExprNode());
		pushResult(send(destObj, node.getMessageName(), getArgument()));
	}else{
		pushResult(send(resolveScope(node.getMessageName(), true), node.getMessageName(), getArgument()));
	}
}
void Machine::walkImpl(const ContNode & node)
{
	eval(node.getFirstNode());
	this->log.t(TAG, &node.location(), "Evaluating continuing node.");
	pushResult(eval(node.getNextNode()));
}

}


 /* namespace machine */
