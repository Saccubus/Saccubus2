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
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::NumericLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::StringLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::AssignNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::OpAssignNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::IndexAcessNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::BindNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::PostOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::PreOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::BinOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::ObjectNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::InvokeNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const tree::ContNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}


} /* namespace machine */
