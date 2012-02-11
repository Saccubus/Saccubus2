/*
 * NodeWalker.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef NODEWALKER_H_
#define NODEWALKER_H_
#include "../classdefs.h"

namespace machine
{

class NodeWalker{
public:
	NodeWalker(){};
	virtual ~NodeWalker(){};
	virtual void walkIn() = 0;
	virtual void walkOut() = 0;
	void walk(const tree::BoolLiteralNode& node);
	void walk(const tree::NumericLiteralNode& node);
	void walk(const tree::StringLiteralNode& node);
	void walk(const tree::AssignNode& node);
	void walk(const tree::OpAssignNode& node);
	void walk(const tree::IndexAcessNode& node);
	void walk(const tree::BindNode& node);
	void walk(const tree::PostOpNode& node);
	void walk(const tree::PreOpNode& node);
	void walk(const tree::BinOpNode& node);
	void walk(const tree::ObjectNode& node);
	void walk(const tree::InvokeNode& node);
	void walk(const tree::ContNode& node);
protected:
	virtual void walkImpl(const tree::BoolLiteralNode& node) = 0;
	virtual void walkImpl(const tree::NumericLiteralNode& node) = 0;
	virtual void walkImpl(const tree::StringLiteralNode& node) = 0;
	virtual void walkImpl(const tree::AssignNode& node) = 0;
	virtual void walkImpl(const tree::OpAssignNode& node) = 0;
	virtual void walkImpl(const tree::IndexAcessNode& node) = 0;
	virtual void walkImpl(const tree::BindNode& node) = 0;
	virtual void walkImpl(const tree::PostOpNode& node) = 0;
	virtual void walkImpl(const tree::PreOpNode& node) = 0;
	virtual void walkImpl(const tree::BinOpNode& node) = 0;
	virtual void walkImpl(const tree::ObjectNode& node) = 0;
	virtual void walkImpl(const tree::InvokeNode& node) = 0;
	virtual void walkImpl(const tree::ContNode& node) = 0;
};

} /* namespace machine */
#endif /* NODEWALKER_H_ */
