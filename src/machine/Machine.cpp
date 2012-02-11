/*
 * Machine::.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Machine.h"

#include "NodeWalker.h"
#include "../tree/Node.h"
#include <tr1/memory>
using namespace tree;
using std::tr1::shared_ptr;
namespace machine{

Machine::Machine()
{
}

Machine::~Machine()
{
}

void Machine::walkIn(){
	bindStack.push(0);
}

void Machine::walkOut(){
	bindStack.pop();
}
void Machine::eval(const Node * node){
	node->accept(*this);
}
void Machine::walkImpl(const BoolLiteralNode & node)
{
	resultStack.push(heap.newBooleanObject(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	resultStack.push(heap.newNumericObject(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	resultStack.push(heap.newStringObject(node.getLiteral()));
}
void Machine::walkImpl(const AssignNode & node)
{
	//InvokeNode* invokeNode = dynamic_cast<InvokeNode*>(&node);
	//Object* lhsObj = eval(node.rightNode);
	//if(invokeNode){

	//}
}
void Machine::walkImpl(const OpAssignNode & node)
{
}
void Machine::walkImpl(const IndexAcessNode & node)
{
}
void Machine::walkImpl(const BindNode & node)
{
	//bindStack.replace(heap.newObject(node.getObjectNode()));
	//eval(node.getExprNode());
}
void Machine::walkImpl(const PostOpNode & node)
{
}
void Machine::walkImpl(const PreOpNode & node)
{
}
void Machine::walkImpl(const BinOpNode & node)
{
}
void Machine::walkImpl(const ObjectNode & node)
{
}
void Machine::walkImpl(const InvokeNode & node)
{
}
void Machine::walkImpl(const ContNode & node)
{
}

} /* namespace machine */
