/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <nekomata/logging/Logging.h>
#include "Node.h"

using nekomata::logging::Dumper;

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
	dumper.printDumpable("leftNode", this->leftNode);
	dumper.printDumpable("rightNode", this->rightNode);
}
void OpAssignNode::dump(Dumper& dumper) const{
	dumper.printName("OpAssignNode:", location());
	dumper.printDumpable("leftNode", this->leftNode);
	dumper.print("op", this->op);
	dumper.printDumpable("rightNode", this->rightNode);
}

void IndexAcessNode::dump(Dumper& dumper) const{
	dumper.printName("IndexAcessNode", location());
	dumper.printDumpable("exprNode", this->exprNode);
	dumper.printDumpable("with obj", this->objectNode);
}
void BindNode::dump(Dumper& dumper) const{
	dumper.printName("BindNode", location());
	dumper.printDumpable("exprNode", this->exprNode);
	dumper.printDumpable("with obj", this->objectNode);
}
void PostOpNode::dump(Dumper& dumper) const{
	dumper.printName("PostOpNode", location());
	dumper.print("op", this->op);
	dumper.printDumpable("exprNode", this->exprNode);
}
void PreOpNode::dump(Dumper& dumper) const{
	dumper.printName("PreOpNode", location());
	dumper.print("op", this->op);
	dumper.printDumpable("exprNode", this->exprNode);
}
void BinOpNode::dump(Dumper& dumper) const{
	dumper.printName("BinOpNode", location());
	dumper.printDumpable("leftNode", this->leftNode);
	dumper.print("op", this->op);
	dumper.printDumpable("rightNode", this->rightNode);
}
void ObjectNode::dump(Dumper& dumper) const{
	dumper.printName("ObjectNode", location());
	std::vector<std::shared_ptr<const nekomata::logging::Dumpable> > list(this->exprList.begin(), this->exprList.end());
	dumper.printDumpableList("exprList", list);
	const std::map<std::string, std::shared_ptr<const nekomata::logging::Dumpable> > map(exprMap.begin(), exprMap.end());
	dumper.printDumpableList("exprMap", map);
}
void InvokeNode::dump(Dumper& dumper) const{
	dumper.printName("InvokeNode", location());
	dumper.print("messageName", this->messageName);
	dumper.printDumpable("exprNode", this->exprNode);
}
void ContNode::dump(Dumper& dumper) const{
	dumper.printName("ContNode", location());
	dumper.printDumpable("firstNode", this->firstNode);
	dumper.printDumpable("nextNode", this->nextNode);
}

}}

