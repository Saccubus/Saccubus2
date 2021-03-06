/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../logging/Dumpable.h"
#include "Location.h"
#include "NodeWalker.h"

namespace nekomata{
namespace tree{

class Node : public logging::Dumpable
{
private:
	const Location loc;
protected:
	explicit Node(const Location& loc):loc(loc){};
	virtual ~Node(){};
public:
	virtual void dump(logging::Dumper& dumper) const = 0;
	const Location& location() const{return loc;};
	virtual void accept(NodeWalker& walker) const = 0;
};

class ExprNode : public Node
{
protected:
	explicit ExprNode(const Location& loc):Node(loc){};
public:
	virtual ~ExprNode(){};
};

class ContNode : public ExprNode
{
private:
	std::shared_ptr<const ExprNode> firstNode;
	std::shared_ptr<const ExprNode> nextNode;
public:
	explicit ContNode(const Location& loc, std::shared_ptr<const ExprNode> fistNode, std::shared_ptr<const ExprNode> nextNode)
	:ExprNode(loc), firstNode(fistNode), nextNode(nextNode){};
	virtual ~ContNode(){};
	void dump(logging::Dumper& dumper) const;
	virtual void accept(NodeWalker& walker) const;
	const ExprNode* getFirstNode() const{return firstNode.get();};
	const ExprNode* getNextNode() const{return nextNode.get();};
};

class InvokeNode : public ExprNode
{
private:
	std::shared_ptr<const ExprNode> exprNode;
	const std::string messageName;
public:
	explicit InvokeNode(const Location& loc, std::shared_ptr<const ExprNode> exprNode, std::string messageName)
	:ExprNode(loc), exprNode(exprNode), messageName(messageName) {};
	virtual ~InvokeNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getExprNode() const{return exprNode.get();}
	std::string const& getMessageName() const{return messageName;}
};

class ObjectNode : public ExprNode
{
private:
	std::map<std::string, std::shared_ptr<const ExprNode> > exprMap;
	std::vector<std::shared_ptr<const ExprNode> > exprList;
public:
	explicit ObjectNode(const Location& loc);
	virtual ~ObjectNode(){};
	void append(std::string name, std::shared_ptr<const ExprNode> exprNode);
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
	bool has(std::string const& name) const{return exprMap.count(name) > 0;}
	bool has(const size_t idx) const{return idx>=0 && idx < exprList.size();}
	const ExprNode* getSlot(std::string const& name) const;
	const ExprNode* index(const size_t idx) const;
	std::vector<std::string> getSlotNames() const;
	size_t size() const;
	size_t slotSize() const;

};

class BinOpNode : public ExprNode{
private:
	std::shared_ptr<const ExprNode> leftNode;
	const std::string op;
	std::shared_ptr<const ExprNode> rightNode;
public:
	explicit BinOpNode(const Location& loc, std::shared_ptr<const ExprNode> leftNode, const std::string op, std::shared_ptr<const ExprNode> rightNode)
		:ExprNode(loc), leftNode(leftNode), op(op), rightNode(rightNode)
	{};
	virtual ~BinOpNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getLeftNode() const{return leftNode.get();}
	std::string const& getOp() const{return op;}
	const ExprNode* getRightNode() const{return rightNode.get();}
};

class PreOpNode : public ExprNode{
private:
	std::shared_ptr<const ExprNode> exprNode;
	std::string op;
public:
	explicit PreOpNode(const Location& loc, std::shared_ptr<const ExprNode> exprNode, std::string op)
		:ExprNode(loc), exprNode(exprNode), op(op)
	{};
	virtual ~PreOpNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getExprNode() const{return exprNode.get();}
	std::string const& getOp() const{return op;}
};

class PostOpNode : public ExprNode{
private:
	std::shared_ptr<const ExprNode> exprNode;
	std::string op;
public:
	explicit PostOpNode(const Location& loc, std::shared_ptr<const ExprNode> exprNode, std::string op)
		:ExprNode(loc), exprNode(exprNode), op(op)
	{};
	virtual ~PostOpNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getExprNode() const{return exprNode.get();}
	std::string const& getOp() const{return op;}
};

class BindNode : public ExprNode
{
private:
	std::shared_ptr<const ExprNode> exprNode;
	std::shared_ptr<const ObjectNode> objectNode;
public:
	explicit BindNode(const Location& loc, std::shared_ptr<const ExprNode> exprNode, std::shared_ptr<const ObjectNode> objectNode)
		:ExprNode(loc), exprNode(exprNode), objectNode(objectNode)
	{};
	virtual ~BindNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ObjectNode* getObjectNode() const{return objectNode.get();}
	const ExprNode* getExprNode() const{return exprNode.get();}
};

class IndexAcessNode : public ExprNode
{
private:
	std::shared_ptr<const ExprNode> exprNode;
	std::shared_ptr<const ObjectNode> objectNode;
public:
	explicit IndexAcessNode(const Location& loc, std::shared_ptr<const ExprNode> exprNode, std::shared_ptr<const ObjectNode> objectNode)
		:ExprNode(loc), exprNode(exprNode), objectNode(objectNode)
	{};
	virtual ~IndexAcessNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getExprNode() const{return exprNode.get();}
	const ObjectNode* getObjectNode() const{return objectNode.get();}
};

class AbstractAssignNode : public ExprNode
{
protected:
	explicit AbstractAssignNode(const Location& loc) : ExprNode(loc) {};
	virtual ~AbstractAssignNode(){};
public:
};

class AssignNode : public AbstractAssignNode
{
private:
	std::shared_ptr<const ExprNode> leftNode;
	std::shared_ptr<const ExprNode> rightNode;
	const bool local;
public:
	explicit AssignNode(const Location& loc, std::shared_ptr<const ExprNode> leftNode, std::shared_ptr<const ExprNode> rightNode, const bool isLocal)
		:AbstractAssignNode(loc), leftNode(leftNode), rightNode(rightNode), local(isLocal)
	{};
	virtual ~AssignNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getLeftNode() const{return leftNode.get();};
	const ExprNode* getRightNode() const{return rightNode.get();};
	bool isLocal() const{return local;};
};

class OpAssignNode : public AbstractAssignNode
{
private:
	std::shared_ptr<const ExprNode> leftNode;
	std::string op;
	std::shared_ptr<const ExprNode> rightNode;
public:
	explicit OpAssignNode(const Location& loc, std::shared_ptr<const ExprNode> leftNode, const std::string op, std::shared_ptr<const ExprNode> rightNode)
		:AbstractAssignNode(loc), leftNode(leftNode), op(op), rightNode(rightNode)
	{};
	virtual ~OpAssignNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
public:
	const ExprNode* getLeftNode() const{return leftNode.get();};
	const ExprNode* getRightNode() const{return rightNode.get();};
	std::string const& getOp() const{return op;}
};

class LiteralNode : public ExprNode
{
private:
public:
	explicit LiteralNode(const Location& loc) : ExprNode(loc) {};
	virtual ~LiteralNode(){};
};

class StringLiteralNode : public LiteralNode
{
private:
	const std::string literal;
public:
	explicit StringLiteralNode(const Location& loc, std::string const& literal);
	virtual ~StringLiteralNode(){};
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;

	std::string const& getLiteral() const;
};

class NumericLiteralNode : public LiteralNode
{
private:
	const double literal;
public:
	explicit NumericLiteralNode(const Location& loc, const double literal);
	virtual ~NumericLiteralNode(){};
	const double getLiteral() const;
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
};

class BoolLiteralNode : public LiteralNode
{
private:
	const bool literal;
public:
	explicit BoolLiteralNode(const Location& loc, const bool literal);
	virtual ~BoolLiteralNode(){};
	const bool getLiteral() const;
	void dump(logging::Dumper& dumper) const;
	void accept(NodeWalker& walker) const;
};

}}
