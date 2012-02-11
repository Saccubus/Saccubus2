/*
 * NodeWalker.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "NodeWalker.h"
#include "../tree/Node.h"

namespace machine
{

void NodeWalker::walk(const tree::BoolLiteralNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::IntegerLiteralNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::StringLiteralNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::AssignNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::OpAssignNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::IndexAcessNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::BindNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::PostOpNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::PreOpNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::BinOpNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::ObjectNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::InvokeNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}
void NodeWalker::walk(const tree::ContNode & node)
{
	walkIn();
	walk(node);
	walkOut();
}


} /* namespace machine */
