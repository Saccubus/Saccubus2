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
,topLevel(heap.newObject())
,log(log)
{
	localStack.push(topLevel);
	selfStack.push(topLevel);
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
	return localStack.top();
}
Object* Machine::newLocal()
{
	Object* const local = heap.newObject();
	localStack.push(local);
	return local;
}
void Machine::endLocal(Object* local)
{
	if(localStack.pop() != local){

	}
}

Object* Machine::resolveScope(const std::string& name, const bool isLocal)
{
	if(name.compare("self") == 0){
		this->log.t(TAG, 0, "Scope Resolved: self");
		return getSelf();
	}else if(name.compare("local") == 0){
		if(isLocal){
			this->log.t(TAG, 0, "Scope Resolved: local");
			return getLocal();
		}else{
			this->log.t(TAG, 0, "Scope Resolved: local(bottom)");
			return localStack.bottom();
		}
	}else if(isLocal){
		for(Stack<Object*>::ReverseIterator it = localStack.rbegin();it!=localStack.rend();++it){
			Object* const obj = *it;
			Object* const slot = obj->getSlot(name);
			if(!slot->isUndefined()){
				this->log.t(TAG, 0, "Scope Resolved: %s", name.c_str());
				return obj;
			}
		}
		this->log.t(TAG, 0, "%s not found.", name.c_str());
		return getLocal();
	}else{
		this->log.t(TAG, 0, "Scope resolved in top level: %s", name.c_str());
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

		pushResult(send(destObj, "setSlot", arg));
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating assign node with index access node.");
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());
		Object* const rhsObj = eval(node.getRightNode());
		pushResult(send(destObj, "indexSet", heap.newArray(idxObj->index(0), rhsObj, 0)));
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating op assign node");
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

		pushResult(send(destObj, "setSlot", heap.newArray(nameObj, result, 0)));
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating op assign node with index access node.");
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());
		Object* const rhsObj = eval(node.getRightNode());

		Object* const operandObj = send(destObj, "index", idxObj);
		Object* const result = send(operandObj, node.getOp(), heap.newArray(rhsObj, 0));

		pushResult(send(destObj, "indexSet", heap.newArray(idxObj->index(0), result, 0)));
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
	this->log.t(TAG, &node.location(), "Evaluating post op node.");
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	if(invokeNode){
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
	}else{
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const PreOpNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating pre op node.");
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	if(invokeNode){
		Object* destObj = 0;
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName(), true);
		}
		StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		Object* operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		Object* const result = send(operandObj, node.getOp());

		pushResult(send(destObj, "setSlot", heap.newArray(nameObj, result, 0)));
	}else{
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const BinOpNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating bin op node.");
	Object* const leftObj = eval(node.getLeftNode());
	Object* const rightObj = eval(node.getRightNode());
	pushResult( send(leftObj, node.getOp(), heap.newArray(rightObj, 0)) );
}
void Machine::walkImpl(const ObjectNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating object node.");
	Object* const obj = heap.newObject();
	//評価していない項目について、すべて評価する
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
		pushResult(send(resolveScope(node.getMessageName()), node.getMessageName(), getArgument()));
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
