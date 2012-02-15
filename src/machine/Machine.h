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

class Machine: public machine::NodeWalker
{
private:
	ObjectHeap heap;
	Stack<Object*> scopeStack;
	Stack<Object*> bindStack;
	Stack<Object*> resultStack;
public:
	Machine();
	virtual ~Machine();
	Object* eval(const tree::Node* node, Object* const with=0);
public: //for Object
	void pushReturnValue(Object* obj);
	Object* fetchBindedObject();
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
