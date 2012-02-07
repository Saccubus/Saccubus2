/*
 * Literal.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "Node.h"

namespace tree{

const logging::Location& LiteralNode::location(){
	return loc;
}

BoolLiteralNode::BoolLiteralNode(const logging::Location& loc, const bool literal)
	:LiteralNode(loc), literal(literal)
{
}

const bool BoolLiteralNode::getLiteral(){
	return literal;
}

StringLiteralNode::StringLiteralNode(const logging::Location & loc, const std::string & literal)
:LiteralNode(loc), literal(literal)
{
}

const std::string& StringLiteralNode::getLiteral()
{
	return literal;
}



IntegerLiteralNode::IntegerLiteralNode(const logging::Location & loc, const int literal)
:LiteralNode(loc), literal(literal)
{
}

const int tree::IntegerLiteralNode::getLiteral()
{
	return literal;
}

}
