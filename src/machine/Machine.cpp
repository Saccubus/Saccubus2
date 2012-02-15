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
{
}

Machine::~Machine()
{
}

void Machine::walkIn(){
}

void Machine::walkOut(){
}

void Machine::pushReturnValue(Object* obj){
	resultStack.push(obj);
}
Object* Machine::fetchBindedObject(){
	return bindStack.top();
}
Object* Machine::resolveScope(const std::string& name, const bool isLocal)
{
	Object* const localObject = scopeStack.top();
	if(!localObject->getSlot(name)->isUndefined()){
		return localObject;
	}
	return scopeStack.bottom();
}

Object* Machine::eval(const Node * node, Object* const with){
	bindStack.push(with);
	node->accept(*this);
	bindStack.pop();
	return resultStack.pop();
}
Object* Machine::eval(Object* const obj, Object* const with){
	bindStack.push(with);
	obj->eval(*this);
	bindStack.pop();
	return resultStack.pop();
}

void Machine::walkImpl(const BoolLiteralNode & node)
{
	pushReturnValue(heap.newBooleanObject(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	pushReturnValue(heap.newNumericObject(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	pushReturnValue(heap.newStringObject(node.getLiteral()));
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
		pushReturnValue(eval(destObj->getSlot("setSlot"), heap.newArray(nameObj,rhsObj, 0)));
	}else{
		pushReturnValue(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
}
void Machine::walkImpl(const IndexAcessNode & node)
{
	Object* const destObj = eval(node.getExprNode());
	pushReturnValue(eval(destObj->getSlot("index"), heap.newArray(heap.newLazyEvalObject(node.getObjectNode()), 0)));
}
void Machine::walkImpl(const BindNode & node)
{
	pushReturnValue(eval(node.getExprNode(), heap.newLazyEvalObject(node.getObjectNode())));
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
	pushReturnValue(result);
}
void Machine::walkImpl(const ObjectNode & node)
{
	Object* const obj = heap.newObject();
	//TODO: ���ׂĂ̎q�m�[�h���W�߂āAeval���č\�z������
	pushReturnValue(obj);
}
void Machine::walkImpl(const InvokeNode & node)
{
	if(node.getExprNode()){
		Object* const destObj = eval(node.getExprNode());
		pushReturnValue(eval(destObj->getSlot(node.getMessageName()), this->fetchBindedObject()));
	}else{
		pushReturnValue(eval(resolveScope(node.getMessageName()), this->fetchBindedObject()));
	}
}
void Machine::walkImpl(const ContNode & node)
{
	eval(node.getFirstNode());
	pushReturnValue(eval(node.getNextNode()));
}

} /* namespace machine */
