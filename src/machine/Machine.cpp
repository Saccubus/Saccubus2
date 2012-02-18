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

Machine::Machine()
:heap()
,topLevel(heap.newObject())
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
		return getSelf();
	}else if(name.compare("local") == 0){
		if(isLocal){
			return getLocal();
		}else{
			return localStack.top();
		}
	}else if(isLocal){
		for(Stack<Object*>::ReverseIterator it = localStack.rbegin();it!=localStack.rend();++it){
			Object* const obj = *it;
			Object* const slot = obj->getSlot(name);
			if(!slot->isUndefined()){
				return obj;
			}
		}
		return getLocal();
	}else{
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
	pushResult(heap.newBooleanObject(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	pushResult(heap.newNumericObject(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	pushResult(heap.newStringObject(node.getLiteral()));
}
void Machine::walkImpl(const AssignNode & node)
{
	if(typeid(node.getLeftNode()) == typeid (InvokeNode)){
		const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
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
	}else if(typeid(node.getLeftNode()) == typeid (IndexAcessNode)){
		const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());
		Object* const rhsObj = eval(node.getRightNode());
		pushResult(send(destObj, "indexSet", heap.newArray(idxObj->index(0), rhsObj, 0)));
	}else{
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
	if(typeid(node.getLeftNode()) == typeid(InvokeNode)){
		const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
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
	}else if(typeid(node.getLeftNode()) == typeid(IndexAcessNode)){
		const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
		Object* const destObj = eval(idxNode->getExprNode());
		Object* const idxObj = eval(idxNode->getObjectNode());
		Object* const rhsObj = eval(node.getRightNode());

		Object* const operandObj = send(destObj, "index", idxObj);
		Object* const result = send(operandObj, node.getOp(), heap.newArray(rhsObj, 0));

		pushResult(send(destObj, "indexSet", heap.newArray(idxObj->index(0), result, 0)));
	}else{
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const IndexAcessNode & node)
{
	Object* const destObj = eval(node.getExprNode());
	pushResult(send(destObj, "index", heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const BindNode & node)
{
	pushResult(eval(node.getExprNode(), heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const PostOpNode & node)
{
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
	Object* const leftObj = eval(node.getLeftNode());
	Object* const rightObj = eval(node.getRightNode());
	pushResult( send(leftObj, node.getOp(), heap.newArray(rightObj, 0)) );
}
void Machine::walkImpl(const ObjectNode & node)
{
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
	pushResult(eval(node.getNextNode()));
}

}


 /* namespace machine */
