/*
 * Literal.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "Node.h"

namespace nekomata{
namespace tree{

BoolLiteralNode::BoolLiteralNode(const logging::Location& loc, const bool literal)
	:LiteralNode(loc), literal(literal)
{
}

const bool BoolLiteralNode::getLiteral() const{
	return literal;
}

StringLiteralNode::StringLiteralNode(const logging::Location & loc, const std::string & literal)
:LiteralNode(loc), literal(literal)
{
}

const std::string& StringLiteralNode::getLiteral() const
{
	return literal;
}



NumericLiteralNode::NumericLiteralNode(const logging::Location & loc, const double literal)
:LiteralNode(loc), literal(literal)
{
}

const double NumericLiteralNode::getLiteral() const
{
	return literal;
}

}
}
