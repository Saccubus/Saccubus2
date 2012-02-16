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
,localObject(heap, 0, localStack)
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
Object* Machine::getLocal(){
	return &localObject;
}
Object* Machine::getSelf(){
	return selfStack.top();
}
Object* Machine::getTopLevel(){
	return selfStack.bottom();
}
Object* Machine::resolveScope(const std::string& name, const bool isLocal)
{
	if(name.compare("self") == 0){
		return selfStack.top();
	}else if(name.compare("local") == 0){
		return &localObject;
	}else if(isLocal){
		return &localObject;
	}else{
		return localStack.bottom();
	}
}

Object* Machine::eval(const Node * node, Object* const with){
	localStack.push(with);
	node->accept(*this);
	localStack.pop();
	return resultStack.pop();
}
Object* Machine::eval(Object* const obj, Object* const with){
	localStack.push(with);
	obj->eval(*this);
	localStack.pop();
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
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	if(invokeNode){
		Object* destObj = 0;
		Object* const rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName(), node.isLocal());
		}
		StringObject* const nameObj = heap.newStringObject(invokeNode->getMessageName());
		pushResult(eval(destObj->getSlot("setSlot"), heap.newArray(nameObj,rhsObj, 0)));
	}else{
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
}
void Machine::walkImpl(const IndexAcessNode & node)
{
	Object* const destObj = eval(node.getExprNode());
	pushResult(eval(destObj->getSlot("index"), heap.newArray(heap.newLazyEvalObject(node.getObjectNode()), 0)));
}
void Machine::walkImpl(const BindNode & node)
{
	pushResult(eval(node.getExprNode(), heap.newLazyEvalObject(node.getObjectNode())));
}
void Machine::walkImpl(const PostOpNode & node)
{
}
void Machine::walkImpl(const PreOpNode & node)
{
}
void Machine::walkImpl(const BinOpNode & node)
{
	Object* const leftObj = eval(node.getLeftNode());
	Object* const rightObj = eval(node.getRightNode());
	Object* const result = eval(leftObj->getSlot(node.getOp()), heap.newArray(rightObj, 0));
	pushResult(result);
}
void Machine::walkImpl(const ObjectNode & node)
{
	Object* const obj = heap.newObject();
	pushResult(obj);
}
void Machine::walkImpl(const InvokeNode & node)
{
	if(node.getExprNode()){
		Object* const destObj = eval(node.getExprNode());
		pushResult(eval(destObj->getSlot(node.getMessageName()), this->localStack.top()));
	}else{
		pushResult(eval(getLocal()->getSlot(node.getMessageName())));
	}
}
void Machine::walkImpl(const ContNode & node)
{
	eval(node.getFirstNode());
	pushResult(eval(node.getNextNode()));
}

}


 /* namespace machine */
