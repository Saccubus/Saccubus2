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

const std::string& StringLiteralNode::getLiteral() const
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