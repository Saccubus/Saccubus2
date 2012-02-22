/*
 * NodeWalker.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef NODEWALKER_H_
#define NODEWALKER_H_
#include "../classdefs.h"

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

}
}
#endif /* NODEWALKER_H_ */
