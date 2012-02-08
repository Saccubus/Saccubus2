/*
 * Object.cpp
 *
 *  Created on: 2012/02/08
 *      Author: psi
 */


#include "Node.h"

namespace tree
{
ObjectNode::ObjectNode(const logging::Location& loc):ExprNode(loc){}
void ObjectNode::append(shared_ptr<const NameNode> nameNode, shared_ptr<const ExprNode> exprNode){
	if(nameNode.get() == 0){
		exprVector.push_back(exprNode);
	}else{
		exprMap.insert(std::pair<std::string, shared_ptr<const ExprNode> >(nameNode->getName(), exprNode));
	}
}

}





