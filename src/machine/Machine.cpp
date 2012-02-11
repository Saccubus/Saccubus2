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
	bindStack.push_back(0);
}

void Machine::walkOut(){
	bindStack.pop_back();
}
void Machine::eval(const Node & node){
}
void Machine::walkImpl(const BoolLiteralNode & node)
{
	//resultStack.push_back(heap.newBoolean(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	//resultStack.push_back(heap.newNumeric(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	//resultStack.push_back(heap.newString(node.getLiteral()));
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
	//bindStack.assign(bindStack.end(), heap.newObject(node.getObjectNode()));
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
