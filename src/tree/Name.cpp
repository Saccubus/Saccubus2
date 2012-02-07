/*
 * Name.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "Node.h"
namespace tree
{
NameNode::NameNode(const logging::Location& loc, const std::string& name)
:loc(loc), name(name)
{

}
NameNode::~NameNode(){

}
const logging::Location& NameNode::location(){
	return loc;
}

const std::string& NameNode::getName(){
	return name;
}

}


