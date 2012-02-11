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
protected:
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
	void eval(const tree::Node* node);
};

} /* namespace machine */
#endif /* MACHINE_H_ */
