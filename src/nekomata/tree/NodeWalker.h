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

#ifndef NODEWALKER_H_
#define NODEWALKER_H_
#include <nekomata/classdefs.h>

namespace nekomata{
namespace tree
{

class NodeWalker{
public:
	NodeWalker(){};
	virtual ~NodeWalker(){};
	virtual void walkIn() = 0;
	virtual void walkOut() = 0;
	void walk(const BoolLiteralNode& node);
	void walk(const NumericLiteralNode& node);
	void walk(const StringLiteralNode& node);
	void walk(const AssignNode& node);
	void walk(const OpAssignNode& node);
	void walk(const IndexAcessNode& node);
	void walk(const BindNode& node);
	void walk(const PostOpNode& node);
	void walk(const PreOpNode& node);
	void walk(const BinOpNode& node);
	void walk(const ObjectNode& node);
	void walk(const InvokeNode& node);
	void walk(const ContNode& node);
protected:
	virtual void walkImpl(const BoolLiteralNode& node) = 0;
	virtual void walkImpl(const NumericLiteralNode& node) = 0;
	virtual void walkImpl(const StringLiteralNode& node) = 0;
	virtual void walkImpl(const AssignNode& node) = 0;
	virtual void walkImpl(const OpAssignNode& node) = 0;
	virtual void walkImpl(const IndexAcessNode& node) = 0;
	virtual void walkImpl(const BindNode& node) = 0;
	virtual void walkImpl(const PostOpNode& node) = 0;
	virtual void walkImpl(const PreOpNode& node) = 0;
	virtual void walkImpl(const BinOpNode& node) = 0;
	virtual void walkImpl(const ObjectNode& node) = 0;
	virtual void walkImpl(const InvokeNode& node) = 0;
	virtual void walkImpl(const ContNode& node) = 0;
};

}}
#endif /* NODEWALKER_H_ */
