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


#include "Node.h"
#include <tr1/memory>
using namespace std::tr1;

namespace nekomata{
namespace tree
{
ObjectNode::ObjectNode(const Location& loc):ExprNode(loc){

}
void ObjectNode::append(std::string name, shared_ptr<const ExprNode> exprNode){
	if(name.size() == 0){
		exprList.push_back(exprNode);
	}else{
		exprMap.insert(std::pair<std::string, shared_ptr<const ExprNode> >(name, exprNode));
	}
}
const ExprNode* ObjectNode::getSlot(const std::string& name) const
{
	std::map<std::string, shared_ptr<const ExprNode> >::const_iterator it = exprMap.find(name);
	if(it != exprMap.end()){
		return it->second.get();
	}else{
		return 0;
	}
}
const ExprNode* ObjectNode::index(const size_t idx) const
{
	if(has(idx)){
		return exprList.at(idx).get();
	}else{
		return 0;
	}
}

std::vector<std::string> ObjectNode::getSlotNames() const

{
	std::vector<std::string> names;
	for(std::map<std::string, shared_ptr<const ExprNode> >::const_iterator it = exprMap.begin(); it != exprMap.end();++it){
		names.push_back(it->first);
	}
	return names;

}
size_t ObjectNode::size() const
{
	return exprList.size();
}
size_t ObjectNode::slotSize() const
{
	return exprMap.size();
}


}}
