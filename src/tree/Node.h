/*
 * Node.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef NODE_H_
#define NODE_H_

#include "../classdefs.h"
#include "../logging/Logging.h"
#include "../machine/NodeWalker.h"
#include <tr1/memory>
#include <map>
#include <vector>

namespace tree
{
using std::tr1::shared_ptr;

class Node : public virtual logging::Dumpable
{
private:
	const logging::Location loc;
protected:
	Node(const logging::Location& loc):loc(loc){};
	virtual ~Node(){};
public:
	//for lexical debug
	virtual void dump(logging::Dumper& dumper) const{}
	const logging::Location& location() const{return loc;};
//	virtual void accept(machine::NodeWalker& walker) = 0;
};

class ExprNode : public Node
{
protected:
	ExprNode(const logging::Location& loc):Node(loc){};
public:
	virtual ~ExprNode(){};
};

class ContNode : public ExprNode
{
private:
	shared_ptr<const ExprNode> fistNode;
	shared_ptr<const ExprNode> nextNode;
public:
	ContNode(const logging::Location& loc, shared_ptr<const ExprNode> fistNode, shared_ptr<const ExprNode> nextNode)
	:ExprNode(loc), fistNode(fistNode), nextNode(nextNode){};
	virtual ~ContNode(){};
};

class InvokeNode : public ExprNode
{
private:
	const shared_ptr<const ExprNode> exprNode;
	const std::string messageName;
public:
	InvokeNode(const logging::Location& loc, shared_ptr<const ExprNode> exprNode, std::string messageName) :ExprNode(loc), exprNode(exprNode), messageName(messageName) {};
	virtual ~InvokeNode(){};
};

class ObjectNode : public ExprNode
{
private:
	std::map<std::string, shared_ptr<const ExprNode> > exprMap;
	std::vector<shared_ptr<const ExprNode> > exprVector;
public:
	ObjectNode(const logging::Location& loc);
	virtual ~ObjectNode(){};
	void append(std::string name, shared_ptr<const ExprNode> exprNode);
};

class BinOpNode : public ExprNode{
private:
	shared_ptr<const ExprNode> leftNode;
	const std::string op;
	shared_ptr<const ExprNode> rightNode;
public:
	BinOpNode(const logging::Location& loc, shared_ptr<const ExprNode> leftNode, const std::string op, shared_ptr<const ExprNode> rightNode)
		:ExprNode(loc), leftNode(leftNode), op(op), rightNode(rightNode)
	{};
	virtual ~BinOpNode(){};
};

class PreOpNode : public ExprNode{
private:
	shared_ptr<const ExprNode> exprNode;
	std::string op;
public:
	PreOpNode(const logging::Location& loc, shared_ptr<const ExprNode> exprNode, std::string op)
		:ExprNode(loc), exprNode(exprNode), op(op)
	{};
	virtual ~PreOpNode(){};
};

class PostOpNode : public ExprNode{
private:
	shared_ptr<const ExprNode> exprNode;
	std::string op;
public:
	PostOpNode(const logging::Location& loc, shared_ptr<const ExprNode> exprNode, std::string op)
		:ExprNode(loc), exprNode(exprNode), op(op)
	{};
	virtual ~PostOpNode(){};
};

class BindNode : public ExprNode
{
private:
	shared_ptr<const ExprNode> exprNode;
	shared_ptr<const ObjectNode> objectNode;
public:
	BindNode(const logging::Location& loc, shared_ptr<const ExprNode> exprNode, shared_ptr<const ObjectNode> objectNode)
		:ExprNode(loc), exprNode(exprNode), objectNode(objectNode)
	{};
	virtual ~BindNode(){};
};

class IndexAcessNode : public ExprNode
{
private:
	shared_ptr<const ExprNode> exprNode;
	shared_ptr<const ObjectNode> objectNode;
public:
	IndexAcessNode(const logging::Location& loc, shared_ptr<const ExprNode> exprNode, shared_ptr<const ObjectNode> objectNode)
		:ExprNode(loc), exprNode(exprNode), objectNode(objectNode)
	{};
	virtual ~IndexAcessNode(){};
};

class AbstractAssignNode : public ExprNode
{
protected:
	AbstractAssignNode(const logging::Location& loc) : ExprNode(loc) {};
	virtual ~AbstractAssignNode(){};
public:
};

class AssignNode : public AbstractAssignNode
{
private:
	shared_ptr<const ExprNode> leftNode;
	shared_ptr<const ExprNode> rightNode;
	const bool isLocal;
public:
	AssignNode(const logging::Location& loc, shared_ptr<const ExprNode> leftNode, shared_ptr<const ExprNode> rightNode, const bool isLocal)
		:AbstractAssignNode(loc), leftNode(leftNode), rightNode(rightNode), isLocal(isLocal)
	{};
	virtual ~AssignNode(){};
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class OpAssignNode : public AbstractAssignNode
{
private:
	shared_ptr<const ExprNode> leftNode;
	std::string op;
	shared_ptr<const ExprNode> rightNode;
public:
	OpAssignNode(const logging::Location& loc, shared_ptr<const ExprNode> leftNode, const std::string op, shared_ptr<const ExprNode> rightNode)
		:AbstractAssignNode(loc), leftNode(leftNode), op(op), rightNode(rightNode)
	{};
	virtual ~OpAssignNode(){};
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class LiteralNode : public ExprNode
{
private:
public:
	LiteralNode(const logging::Location& loc) : ExprNode(loc) {};
	virtual ~LiteralNode(){};
};

class StringLiteralNode : public LiteralNode
{
private:
	const std::string literal;
public:
	StringLiteralNode(const logging::Location& loc, const std::string& literal);
	virtual ~StringLiteralNode(){};

	const std::string& getLiteral() const;
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class IntegerLiteralNode : public LiteralNode
{
private:
	const int literal;
public:
	IntegerLiteralNode(const logging::Location& loc, const int literal);
	virtual ~IntegerLiteralNode(){};
	const int getLiteral() const;
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class BoolLiteralNode : public LiteralNode
{
private:
	const bool literal;
public:
	BoolLiteralNode(const logging::Location& loc, const bool literal);
	virtual ~BoolLiteralNode(){};
	const bool getLiteral() const;
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

} /* namespace tree */
#endif /* NODE_H_ */
