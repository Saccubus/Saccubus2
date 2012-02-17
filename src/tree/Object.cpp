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
ObjectNode::ObjectNode(const logging::Location& loc):ExprNode(loc){

}
void ObjectNode::append(std::string name, shared_ptr<const ExprNode> exprNode){
	if(name.size() == 0){
		exprList.push_back(exprNode);
	}else{
		exprMap.insert(std::pair<std::string, shared_ptr<const ExprNode> >(name, exprNode));
	}
}
const ExprNode* ObjectNode::getNode(const std::string& name) const
{
	std::map<std::string, shared_ptr<const ExprNode> >::const_iterator it = exprMap.find(name);
	if(it != exprMap.end()){
		return it->second.get();
	}else{
		return 0;
	}
}
const ExprNode* ObjectNode::getNode(const size_t idx) const
{
	if(hasNode(idx)){
		return exprList.at(idx).get();
	}else{
		return 0;
	}
}

}





