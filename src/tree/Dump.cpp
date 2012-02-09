/*
 * Dump.cpp
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */
#include "Node.h"
#include "../logging/Logging.h"

using logging::Dumper;
using namespace tree;

void BoolLiteralNode::dump(Dumper& dumper) const{
	dumper.printName("BoolLiteralNode");
	dumper.print("literal", (bool)this->literal);
}
void IntegerLiteralNode::dump(Dumper& dumper) const{
	dumper.printName("IntegerLiteralNode");
	dumper.print("literal", (int)this->literal);
}
void StringLiteralNode::dump(Dumper& dumper) const{
	dumper.printName("StringLiteralNode");
	dumper.print("literal", (std::string&)this->literal);
}

void AssignNode::dump(Dumper& dumper) const{
	dumper.printName("AssignNode");
	dumper.print("isLocal?", isLocal);
	dumper.printNode("leftNode", (shared_ptr<const Dumpable>&)this->leftNode);
	dumper.printNode("rightNode", (shared_ptr<const Dumpable>&)this->rightNode);
}
void OpAssignNode::dump(Dumper& dumper) const{
	dumper.printName("OpAssignNode:");
	dumper.printNode("leftNode", (shared_ptr<const Dumpable>&)this->leftNode);
	dumper.print("op", this->op);
	dumper.printNode("rightNode", (shared_ptr<const Dumpable>&)this->rightNode);
}

void IndexAcessNode::dump(Dumper& dumper) const{
	dumper.printName("IndexAcessNode");
	dumper.printNode("exprNode", (shared_ptr<const Dumpable>&)this->exprNode);
	dumper.printNode("with obj", (shared_ptr<const Dumpable>&)this->objectNode);
}
void BindNode::dump(Dumper& dumper) const{
	dumper.printName("BindNode");
	dumper.printNode("exprNode", (shared_ptr<const Dumpable>&)this->exprNode);
	dumper.printNode("with obj", (shared_ptr<const Dumpable>&)this->objectNode);
}
void PostOpNode::dump(Dumper& dumper) const{
	dumper.printName("PostOpNode");
	dumper.print("op", this->op);
	dumper.printNode("exprNode", (shared_ptr<const Dumpable>&)this->exprNode);
}
void PreOpNode::dump(Dumper& dumper) const{
	dumper.printName("PreOpNode");
	dumper.print("op", this->op);
	dumper.printNode("exprNode", (shared_ptr<const Dumpable>&)this->exprNode);
}
void BinOpNode::dump(Dumper& dumper) const{
	dumper.printName("BinOpNode");
	dumper.printNode("leftNode", (shared_ptr<const Dumpable>&)this->leftNode);
	dumper.print("op", this->op);
	dumper.printNode("rightNode", (shared_ptr<const Dumpable>&)this->rightNode);
}
void ObjectNode::dump(Dumper& dumper) const{
	dumper.printName("ObjectNode");
	dumper.printNodeList("exprVector", (std::vector<shared_ptr<const Dumpable> >&)this->exprVector);
	dumper.printNodeList("exprMap", (std::map<std::string, std::tr1::shared_ptr<const Dumpable> >&)this->exprMap);
}
void InvokeNode::dump(Dumper& dumper) const{
	dumper.printName("InvokeNode");
	dumper.print("messageName", this->messageName);
	dumper.printNode("exprNode", (shared_ptr<const Dumpable>&)this->exprNode);
}
void ContNode::dump(Dumper& dumper) const{
	dumper.printName("ContNode");
	dumper.printNode("firstNode", (shared_ptr<const Dumpable>&)this->firstNode);
	dumper.printNode("nextNode", (shared_ptr<const Dumpable>&)this->nextNode);
}



