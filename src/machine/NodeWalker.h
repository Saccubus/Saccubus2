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
	virtual void walk(const tree::BoolLiteralNode& node) =0;
	virtual void walk(const tree::IntegerLiteralNode& node) =0;
	virtual void walk(const tree::StringLiteralNode& node) =0;
	virtual void walk(const tree::AssignNode& node) =0;
	virtual void walk(const tree::OpAssignNode& node) =0;
	virtual void walk(const tree::IndexAcessNode& node) =0;
	virtual void walk(const tree::BindNode& node) =0;
	virtual void walk(const tree::PostOpNode& node) =0;
	virtual void walk(const tree::PreOpNode& node) =0;
	virtual void walk(const tree::BinOpNode& node) =0;
	virtual void walk(const tree::ObjectNode& node) =0;
	virtual void walk(const tree::InvokeNode& node) =0;
	virtual void walk(const tree::ContNode& node) =0;
};

} /* namespace machine */
#endif /* NODEWALKER_H_ */
