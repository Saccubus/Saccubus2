/*
 * Object.cpp
 *
 *  Created on: 2012/02/08
 *      Author: psi
 */


#include "Node.h"
#include <tr1/memory>
using namespace std::tr1;

namespace tree
{
ObjectNode::ObjectNode(const logging::Location& loc):ExprNode(loc){}
void ObjectNode::append(std::string name, shared_ptr<const ExprNode> exprNode){
	if(name.size() == 0){
		exprVector.push_back(exprNode);
	}else{
		exprMap.insert(std::pair<std::string, shared_ptr<const ExprNode> >(name, exprNode));
	}
}

}





