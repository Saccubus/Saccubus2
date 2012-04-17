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

#ifndef MACHINE_H_
#define MACHINE_H_
#include <vector>
#include <map>
#include <nekomata/classdefs.h>
#include "../object/Heap.h"
#include "../tree/NodeWalker.h"
#include "Stack.h"

namespace nekomata{
namespace machine{

class Machine: public tree::NodeWalker, public object::RootHolder
{
private:
	object::ObjectHeap heap;
	Stack<object::Object*> argStack;
	Stack<object::Object*> selfStack;
	Stack<object::Object*> resultStack;
	Stack<object::Object*> scopeStack;
	std::vector<Stack<object::Object*>* > rootStacks;
public:
	explicit Machine(logging::Logger& log, system::System& system);
	virtual ~Machine();
	object::Handler<object::Object> eval(const tree::Node* node, const object::Handler<object::Object>& arg=object::Handler<object::Object>(0));
	object::Handler<object::Object> send(const object::Handler<object::Object>& self, const std::string& message, const object::Handler<object::Object>& arg=object::Handler<object::Object>(0));
	logging::Logger& log;
public: //for Object
	void pushResult(object::Handler<object::Object> obj);
	object::Handler<object::Object> getArgument();
	object::Handler<object::Object> getLocal();
	object::Handler<object::Object> getSelf();
	object::Handler<object::SystemObject> getTopLevel();
	void enterLocal(object::Handler<object::Object> local, object::Handler<object::Object> parent=object::Handler<object::Object>(0));
	void endLocal(object::Handler<object::Object> local);
protected: //for tree
	void walkIn();
	void walkOut();
	void walkImpl(const tree::BoolLiteralNode& node);
	void walkImpl(const tree::NumericLiteralNode& node);
	void walkImpl(const tree::StringLiteralNode& node);
	void walkImpl(const tree::AssignNode& node);
	void walkImpl(const tree::OpAssignNode& node);
	void walkImpl(const tree::IndexAcessNode& node);
	void walkImpl(const tree::BindNode& node);
	void walkImpl(const tree::PostOpNode& node);
	void walkImpl(const tree::PreOpNode& node);
	void walkImpl(const tree::BinOpNode& node);
	void walkImpl(const tree::ObjectNode& node);
	void walkImpl(const tree::InvokeNode& node);
	void walkImpl(const tree::ContNode& node);
private:
	object::Handler<object::Object> resolveScope(const std::string& name);
private:
	class RootIterator : public object::RootHolder::Iterator
	{
	private:
		std::vector<Stack<object::Object*>*>::const_iterator pCurrent;
		std::vector<Stack<object::Object*>*>::const_iterator pEnd;
		Stack<object::Object*>::Iterator current;
		Stack<object::Object*>::Iterator end;
		void nextStack();
	public:
		RootIterator(std::vector<Stack<object::Object*>*>::const_iterator start, std::vector<Stack<object::Object*>*>::const_iterator end);
		virtual ~RootIterator();
		virtual bool hasNext();
		virtual object::Object* next();
	};
public:
	virtual object::RootHolder::Iterator* newIterator();
};

}}
#endif /* MACHINE_H_ */
