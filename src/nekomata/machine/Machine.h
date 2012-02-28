/*
 * Machine.h
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include <vector>
#include <map>
#include "../classdefs.h"
#include "../object/Heap.h"
#include "../tree/NodeWalker.h"
#include "Stack.h"

namespace nekomata{
namespace machine{

class Machine: public tree::NodeWalker, public object::ObjectHeap::GarbageCollectionCallback
{
private:
	object::ObjectHeap heap;
	Stack<object::Object*> argStack;
	Stack<object::Object*> selfStack;
	Stack<object::Object*> resultStack;
	Stack<object::Object*> scopeStack;
public:
	explicit Machine(logging::Logger& log, system::System& system);
	virtual ~Machine();
	object::Object* eval(const nekomata::tree::Node* node, object::Object* const arg=0);
	object::Object* send(object::Object* const self, const std::string& message, object::Object* const arg=0);
	logging::Logger& log;
public:
	void needGC(object::ObjectHeap& self);
public: //for Object
	void pushResult(object::Object* obj);
	object::Object* getArgument();
	object::Object* getLocal();
	object::Object* getSelf();
	object::Object* getTopLevel();
	void enterLocal(object::Object* local, object::Object* parent = 0);
	void endLocal(object::Object* local);
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
	object::Object* resolveScope(const std::string& name);
};

}
}
#endif /* MACHINE_H_ */
