/*
 * Dump.cpp
 *
 *  Created on: 2012/02/09
 *      Author: psi
 */
#include "Node.h"

using nekomata::logging::Dumper;
using namespace std::tr1;

namespace nekomata{
namespace tree{
void BoolLiteralNode::dump(Dumper& dumper) const{
	dumper.printName("BoolLiteralNode", location());
	dumper.print("literal", this->literal);
}
void NumericLiteralNode::dump(Dumper& dumper) const{
	dumper.printName("NumericLiteralNode", location());
	dumper.print("literal", this->literal);
}
void StringLiteralNode::dump(Dumper& dumper) const{
	dumper.printName("StringLiteralNode", location());
	dumper.print("literal", this->literal);
}

void AssignNode::dump(Dumper& dumper) const{
	dumper.printName("AssignNode", location());
	dumper.print("isLocal?", local);
	dumper.printNode("leftNode", this->leftNode);
	dumper.printNode("rightNode", this->rightNode);
}
void OpAssignNode::dump(Dumper& dumper) const{
	dumper.printName("OpAssignNode:", location());
	dumper.printNode("leftNode", this->leftNode);
	dumper.print("op", this->op);
	dumper.printNode("rightNode", this->rightNode);
}

void IndexAcessNode::dump(Dumper& dumper) const{
	dumper.printName("IndexAcessNode", location());
	dumper.printNode("exprNode", this->exprNode);
	dumper.printNode("with obj", this->objectNode);
}
void BindNode::dump(Dumper& dumper) const{
	dumper.printName("BindNode", location());
	dumper.printNode("exprNode", this->exprNode);
	dumper.printNode("with obj", this->objectNode);
}
void PostOpNode::dump(Dumper& dumper) const{
	dumper.printName("PostOpNode", location());
	dumper.print("op", this->op);
	dumper.printNode("exprNode", this->exprNode);
}
void PreOpNode::dump(Dumper& dumper) const{
	dumper.printName("PreOpNode", location());
	dumper.print("op", this->op);
	dumper.printNode("exprNode", this->exprNode);
}
void BinOpNode::dump(Dumper& dumper) const{
	dumper.printName("BinOpNode", location());
	dumper.printNode("leftNode", this->leftNode);
	dumper.print("op", this->op);
	dumper.printNode("rightNode", this->rightNode);
}
void ObjectNode::dump(Dumper& dumper) const{
	dumper.printName("ObjectNode", location());
	dumper.printDumpableList("exprList", (const std::vector<shared_ptr<const Dumpable> >&)this->exprList);
	dumper.printDumpableList("exprMap", (const std::map<std::string, shared_ptr<const Dumpable> >&)this->exprMap);
}
void InvokeNode::dump(Dumper& dumper) const{
	dumper.printName("InvokeNode", location());
	dumper.print("messageName", this->messageName);
	dumper.printNode("exprNode", this->exprNode);
}
void ContNode::dump(Dumper& dumper) const{
	dumper.printName("ContNode", location());
	dumper.printNode("firstNode", this->firstNode);
	dumper.printNode("nextNode", this->nextNode);
}

}
}

