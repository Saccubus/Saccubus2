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
#include "NodeWalker.h"

namespace nekomata{
namespace tree{

void NodeWalker::walk(const BoolLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const NumericLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const StringLiteralNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const AssignNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const OpAssignNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const IndexAcessNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const BindNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const PostOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const PreOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const BinOpNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const ObjectNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const InvokeNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}
void NodeWalker::walk(const ContNode & node)
{
	walkIn();
	walkImpl(node);
	walkOut();
}


}}
