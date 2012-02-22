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
#include "object/Object.h"
#include "object/Heap.h"
#include "../tree/NodeWalker.h"
#include "Stack.h"

namespace nekomata{
namespace machine{

class Machine: public tree::NodeWalker, public ObjectHeap::GarbageCollectionCallback
{
private:
	ObjectHeap heap;
	Stack<Object*> argStack;
	Stack<Object*> selfStack;
	Stack<Object*> resultStack;
	Stack<Object*> scopeStack;
public:
	explicit Machine(logging::Logger& log);
	virtual ~Machine();
	Object* eval(const nekomata::tree::Node* node, Object* const arg=0);
	Object* send(Object* const self, const std::string& message, Object* const arg=0);
	logging::Logger& log;
public:
	void needGC(ObjectHeap& self);
public: //for Object
	void pushResult(Object* obj);
	Object* getArgument();
	Object* getLocal();
	Object* getSelf();
	Object* getTopLevel();
	void enterLocal(Object* local, Object* parent = 0);
	void endLocal(Object* local);
protected: //for tree
	void walkIn();
	void walkOut();
	void walkImpl(const nekomata::tree::BoolLiteralNode& node);
	void walkImpl(const nekomata::tree::NumericLiteralNode& node);
	void walkImpl(const nekomata::tree::StringLiteralNode& node);
	void walkImpl(const nekomata::tree::AssignNode& node);
	void walkImpl(const nekomata::tree::OpAssignNode& node);
	void walkImpl(const nekomata::tree::IndexAcessNode& node);
	void walkImpl(const nekomata::tree::BindNode& node);
	void walkImpl(const nekomata::tree::PostOpNode& node);
	void walkImpl(const nekomata::tree::PreOpNode& node);
	void walkImpl(const nekomata::tree::BinOpNode& node);
	void walkImpl(const nekomata::tree::ObjectNode& node);
	void walkImpl(const nekomata::tree::InvokeNode& node);
	void walkImpl(const nekomata::tree::ContNode& node);
private:
	Object* resolveScope(const std::string& name);
};

}
}
#endif /* MACHINE_H_ */
