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
#include "object/Object.h"
#include "object/Heap.h"
#include "NodeWalker.h"
#include "Stack.h"
namespace machine
{
class LocalObject : public Object{
private:
	Stack<Object*>& localStack;
public:
	LocalObject(ObjectHeap& heap, const unsigned int hash, Stack<Object*>& localStack);
	virtual ~LocalObject();
public:
	virtual void inject(Object* to);
	virtual int push(Object* const item);
	virtual Object* index(size_t idx);
	virtual Object* setSlot(const std::string& name, Object* const item);
	virtual Object* getSlot(const std::string& name);
	virtual bool isUndefined();
	virtual void eval(Machine& machine);
	virtual StringObject* toStringObject();
	virtual NumericObject* toNumericObject();
	virtual BooleanObject* toBooleanObject();
};

class Machine: public machine::NodeWalker
{
private:
	ObjectHeap heap;
	Stack<Object*> selfStack;
	Stack<Object*> localStack;
	Stack<Object*> resultStack;
	Object* topLevel;
	LocalObject localObject;
public:
	Machine();
	virtual ~Machine();
	Object* eval(const tree::Node* node, Object* const with=0);
public: //for Object
	void pushResult(Object* obj);
	Object* getLocal();
	Object* getSelf();
	Object* getTopLevel();
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
	Object* eval(Object* const obj, Object* const with=0);
	Object* resolveScope(const std::string& name, const bool isLocal=true);
};

} /* namespace machine */
#endif /* MACHINE_H_ */
