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
#include "NodeWalker.h"
#include "Stack.h"
namespace machine
{

class Machine: public machine::NodeWalker, public ObjectHeap::GarbageCollectionCallback
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
	Object* eval(const tree::Node* node, Object* const arg=0);
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
	Object* resolveScope(const std::string& name);
};

} /* namespace machine */
#endif /* MACHINE_H_ */
