/*
 * Machine::.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Machine.h"

#include "../tree/NodeWalker.h"
#include "../object/Object.h"
#include "../object/Heap.h"
#include "../tree/Node.h"
#include <tr1/memory>
using namespace nekomata::tree;
using std::tr1::shared_ptr;

namespace nekomata{
namespace machine{

static const std::string TAG("Machine");

Machine::Machine(logging::Logger& log, system::System& system)
:heap(log, system, *this)
,log(log)
{
	selfStack.push(heap.getSystemObject());
	this->enterLocal(heap.getSystemObject(), heap.newUndefinedObject());
}

Machine::~Machine()
{
}

void Machine::walkIn(){
}

void Machine::walkOut(){
	heap.checkGC();
}

void Machine::pushResult(object::Object* obj){
	resultStack.push(obj);
}
object::Object* Machine::getArgument(){
	return argStack.top();
}
object::Object* Machine::getSelf(){
	return selfStack.top();
}
object::Object* Machine::getTopLevel(){
	return selfStack.bottom();
}
object::Object* Machine::getLocal()
{
	return scopeStack.top();
}
void Machine::enterLocal(object::Object* local, object::Object* parent)
{
	if(parent){
		local->setSlot("$$parent", parent);
	}
	scopeStack.push(local);
}
void Machine::endLocal(object::Object* local)
{
	if(scopeStack.top() != local){
		this->log.e(TAG, 0, "[BUG] calling \"end local\" was forgotten!");
	}
	scopeStack.pop();
}

object::Object* Machine::resolveScope(const std::string& name)
{
	if(name.compare("self") == 0){
		this->log.t(TAG, 0, "Scope Resolved: self");
		return getSelf();
	}else if(name.compare("local") == 0){
		this->log.t(TAG, 0, "Scope Resolved: \"local\"");
		return getLocal();
	}else{
		for(object::Object* obj = getLocal();!obj->isUndefined();obj=obj->getSlot("$$parent")){
			object::Object* const slot = obj->getSlot(name);
			if(!slot->isUndefined()){
				this->log.t(TAG, 0, "Scope Resolved: %s in %s", name.c_str(), obj->toStringObject()->toString().c_str());
				return obj;
			}
		}
		this->log.t(TAG, 0, "%s not found.", name.c_str());
		return getLocal();
	}
}

object::Object* Machine::eval(const Node * node, object::Object* const arg){
	if(arg){
		argStack.push(arg);
	}else{
		argStack.push(heap.newUndefinedObject());
	}
	node->accept(*this);
	argStack.pop();
	return resultStack.pop();
}
object::Object* Machine::send(object::Object* const self, const std::string& message, object::Object* const arg){
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

void Machine::needGC(object::ObjectHeap& self)
{
	std::vector<object::Object*> objList;
	argStack.merge(objList);
	selfStack.merge(objList);
	scopeStack.merge(objList);
	resultStack.merge(objList);
	self.gc(objList);
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
		object::Object* destObj = 0;
		object::Object* const rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			if(node.isLocal()){
				destObj = getLocal();
			}else{
				destObj = resolveScope(invokeNode->getMessageName());
			}
		}
		object::StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());
		object::Object* const arg = heap.newArray(nameObj,rhsObj, 0);

		send(destObj, "setSlot", arg);
		pushResult(rhsObj);
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating assign node with index access node.");
		object::Object* const destObj = eval(idxNode->getExprNode());
		object::Object* const idxObj = eval(idxNode->getObjectNode());
		object::Object* const rhsObj = eval(node.getRightNode());

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
			object::Object* destObj = 0;
		object::Object* const rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		object::StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Object* const operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		object::Object* const result = send(operandObj, node.getOp(), heap.newArray(rhsObj, 0));

		send(destObj, "setSlot", heap.newArray(nameObj, result, 0));
		pushResult(result);
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating op assign node with index access node.");
		object::Object* const destObj = eval(idxNode->getExprNode());
		object::Object* const idxObj = eval(idxNode->getObjectNode());
		object::Object* const rhsObj = eval(node.getRightNode());

		object::Object* const operandObj = send(destObj, "index", idxObj);
		object::Object* const result = send(operandObj, node.getOp(), heap.newArray(rhsObj, 0));

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
	object::Object* const destObj = eval(node.getExprNode());
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
		object::Object* destObj = 0;
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		object::StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Object* operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		object::Object* const result = send(operandObj, node.getOp());

		send(destObj, "setSlot", heap.newArray(nameObj, result, 0));
		pushResult(operandObj);
	}else if(idxNode){
		this->log.t(TAG, &node.location(), "Evaluating post op node with index access node: %s", node.getOp().c_str());
		object::Object* const destObj = eval(idxNode->getExprNode());
		object::Object* const idxObj = eval(idxNode->getObjectNode());

		object::Object* const operandObj = send(destObj, "index", idxObj);
		object::Object* const result = send(operandObj, node.getOp());

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
		object::Object* destObj = 0;
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		object::StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Object* operandObj = send(destObj, "getSlot", heap.newArray(nameObj, 0));
		object::Object* const result = send(operandObj, node.getOp());
		send(destObj, "setSlot", heap.newArray(nameObj, result, 0));

		pushResult(result);
	}else if(idxNode){
		this->log.t(TAG, &node.location(), "Evaluating pre op node with index access node: %s", node.getOp().c_str());
		object::Object* const destObj = eval(idxNode->getExprNode());
		object::Object* const idxObj = eval(idxNode->getObjectNode());

		object::Object* const operandObj = send(destObj, "index", idxObj);
		object::Object* const result = send(operandObj, node.getOp());

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
	object::Object* const leftObj = eval(node.getLeftNode());
	object::Object* const rightObj = eval(node.getRightNode());
	pushResult( send(leftObj, node.getOp(), heap.newArray(rightObj, 0)) );
}
void Machine::walkImpl(const ObjectNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating object node.");
	object::Object* const obj = heap.newObject();

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
		object::Object* const destObj = eval(node.getExprNode());
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
}
