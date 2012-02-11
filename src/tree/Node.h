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
#include <map>
#include <vector>
#include <tr1/memory>

namespace tree
{

class Node : public logging::Dumpable
{
private:
	const logging::Location loc;
protected:
	Node(const logging::Location& loc):loc(loc){};
	virtual ~Node(){};
public:
	virtual void dump(logging::Dumper& dumper) const = 0;
	const logging::Location& location() const{return loc;};
	virtual void accept(machine::NodeWalker& walker) const = 0;
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
	std::tr1::shared_ptr<const ExprNode> firstNode;
	std::tr1::shared_ptr<const ExprNode> nextNode;
public:
	ContNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> fistNode, std::tr1::shared_ptr<const ExprNode> nextNode)
	:ExprNode(loc), firstNode(fistNode), nextNode(nextNode){};
	virtual ~ContNode(){};
	void dump(logging::Dumper& dumper) const;
	virtual void accept(machine::NodeWalker& walker) const;
};

class InvokeNode : public ExprNode
{
private:
	std::tr1::shared_ptr<const ExprNode> exprNode;
	const std::string messageName;
public:
	InvokeNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> exprNode, std::string messageName)
	:ExprNode(loc), exprNode(exprNode), messageName(messageName) {};
	virtual ~InvokeNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

class ObjectNode : public ExprNode
{
private:
	std::map<std::string, std::tr1::shared_ptr<const ExprNode> > exprMap;
	std::vector<std::tr1::shared_ptr<const ExprNode> > exprVector;
public:
	ObjectNode(const logging::Location& loc);
	virtual ~ObjectNode(){};
	void append(std::string name, std::tr1::shared_ptr<const ExprNode> exprNode);
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

class BinOpNode : public ExprNode{
private:
	std::tr1::shared_ptr<const ExprNode> leftNode;
	const std::string op;
	std::tr1::shared_ptr<const ExprNode> rightNode;
public:
	BinOpNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> leftNode, const std::string op, std::tr1::shared_ptr<const ExprNode> rightNode)
		:ExprNode(loc), leftNode(leftNode), op(op), rightNode(rightNode)
	{};
	virtual ~BinOpNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

class PreOpNode : public ExprNode{
private:
	std::tr1::shared_ptr<const ExprNode> exprNode;
	std::string op;
public:
	PreOpNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> exprNode, std::string op)
		:ExprNode(loc), exprNode(exprNode), op(op)
	{};
	virtual ~PreOpNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

class PostOpNode : public ExprNode{
private:
	std::tr1::shared_ptr<const ExprNode> exprNode;
	std::string op;
public:
	PostOpNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> exprNode, std::string op)
		:ExprNode(loc), exprNode(exprNode), op(op)
	{};
	virtual ~PostOpNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

class BindNode : public ExprNode
{
private:
	std::tr1::shared_ptr<const ExprNode> exprNode;
	std::tr1::shared_ptr<const ObjectNode> objectNode;
public:
	BindNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> exprNode, std::tr1::shared_ptr<const ObjectNode> objectNode)
		:ExprNode(loc), exprNode(exprNode), objectNode(objectNode)
	{};
	virtual ~BindNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
	std::tr1::shared_ptr<const ObjectNode> getObjectNode() const{return objectNode;}
	std::tr1::shared_ptr<const ExprNode> getExprNode() const{return exprNode;}

};

class IndexAcessNode : public ExprNode
{
private:
	std::tr1::shared_ptr<const ExprNode> exprNode;
	std::tr1::shared_ptr<const ObjectNode> objectNode;
public:
	IndexAcessNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> exprNode, std::tr1::shared_ptr<const ObjectNode> objectNode)
		:ExprNode(loc), exprNode(exprNode), objectNode(objectNode)
	{};
	virtual ~IndexAcessNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
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
	std::tr1::shared_ptr<const ExprNode> leftNode;
	std::tr1::shared_ptr<const ExprNode> rightNode;
	const bool isLocal;
public:
	AssignNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> leftNode, std::tr1::shared_ptr<const ExprNode> rightNode, const bool isLocal)
		:AbstractAssignNode(loc), leftNode(leftNode), rightNode(rightNode), isLocal(isLocal)
	{};
	virtual ~AssignNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;

};

class OpAssignNode : public AbstractAssignNode
{
private:
	std::tr1::shared_ptr<const ExprNode> leftNode;
	std::string op;
	std::tr1::shared_ptr<const ExprNode> rightNode;
public:
	OpAssignNode(const logging::Location& loc, std::tr1::shared_ptr<const ExprNode> leftNode, const std::string op, std::tr1::shared_ptr<const ExprNode> rightNode)
		:AbstractAssignNode(loc), leftNode(leftNode), op(op), rightNode(rightNode)
	{};
	virtual ~OpAssignNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
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
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;

	const std::string& getLiteral() const;
};

class NumericLiteralNode : public LiteralNode
{
private:
	const double literal;
public:
	NumericLiteralNode(const logging::Location& loc, const double literal);
	virtual ~NumericLiteralNode(){};
	const double getLiteral() const;
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

class BoolLiteralNode : public LiteralNode
{
private:
	const bool literal;
public:
	BoolLiteralNode(const logging::Location& loc, const bool literal);
	virtual ~BoolLiteralNode(){};
	const bool getLiteral() const;
	void dump(logging::Dumper& dumper) const;
	void accept(machine::NodeWalker& walker) const;
};

} /* namespace tree */
#endif /* NODE_H_ */
