/*
 * NodeWalker.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "Node.h"
#include "NodeWalker.h"

namespace nekomata{
namespace tree{

void NodeWalker::walk(const BoolLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const NumericLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const StringLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const AssignNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const OpAssignNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const IndexAcessNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const BindNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const PostOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const PreOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const BinOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const ObjectNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const InvokeNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const ContNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}


}
}
