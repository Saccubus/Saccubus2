/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "Node.h"

namespace nekomata{
namespace tree{

BoolLiteralNode::BoolLiteralNode(const Location& loc, const bool literal)
	:LiteralNode(loc), literal(literal)
{
}

const bool BoolLiteralNode::getLiteral() const{
	return literal;
}

StringLiteralNode::StringLiteralNode(const Location & loc, const std::string & literal)
:LiteralNode(loc), literal(literal)
{
}

std::string const& StringLiteralNode::getLiteral() const
{
	return literal;
}



NumericLiteralNode::NumericLiteralNode(const Location & loc, const double literal)
:LiteralNode(loc), literal(literal)
{
}

const double NumericLiteralNode::getLiteral() const
{
	return literal;
}

}}
