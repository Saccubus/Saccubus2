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

class NameNode : public Node
{
private:
	const std::string& name;
public:
	NameNode(const logging::Location& loc, const std::string& name) :Node(loc), name(name) {};
	virtual ~NameNode(){};
	const std::string getName() const {return name;};
};

class SlotNode : public ExprNode
{
private:
	const shared_ptr<const ExprNode> scope;
	const shared_ptr<const NameNode> nameNode;
public:
	SlotNode(const logging::Location& loc, shared_ptr<const ExprNode>, shared_ptr<const NameNode> nameNode) :ExprNode(loc), scope(scope), nameNode(nameNode) {};
	virtual ~SlotNode(){};
	const shared_ptr<const NameNode> getNameNode() const {return nameNode;};
	const shared_ptr<const ExprNode> getScopeNode() const{return scope;};
};

class ObjectNode : public ExprNode
{
private:
	std::map<std::string, shared_ptr<const ExprNode> > exprMap;
	std::vector<shared_ptr<const ExprNode> > exprVector;
public:
	ObjectNode(const logging::Location& loc);
	virtual ~ObjectNode(){};
	void append(shared_ptr<const NameNode> nameNode, shared_ptr<const ExprNode> exprNode);
};

class CallNode : public ExprNode
{
public:
	CallNode();
	virtual ~CallNode(){};
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
	AssignNode(const logging::Location& loc);
	virtual ~AssignNode();
public:
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class OpAssignNode : public AbstractAssignNode
{
	OpAssignNode(const logging::Location& loc);
	virtual ~OpAssignNode();
public:
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
