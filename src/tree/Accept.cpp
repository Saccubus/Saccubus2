/*
 * Accept.cpp
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */

#include "Node.h"
#include "../machine/NodeWalker.h"

using namespace tree;
using namespace machine;

void BoolLiteralNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void NumericLiteralNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void StringLiteralNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}

void AssignNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void OpAssignNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void IndexAcessNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void BindNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void PostOpNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void PreOpNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void BinOpNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void ObjectNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void InvokeNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void ContNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}



