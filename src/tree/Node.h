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

namespace tree
{

class Node : public virtual logging::Dumpable
{
protected:
	Node(){};
	virtual ~Node(){};
public:
	virtual const logging::Location& location() = 0;
	//for lexical debug
	virtual void dump(logging::Dumper& dumper){}
//	virtual void accept(machine::NodeWalker& walker) = 0;
};

class ExprNode : public Node
{
protected:
	ExprNode(){};
	virtual ~ExprNode(){};
public:
};

class NameNode : public ExprNode
{
private:
	const logging::Location loc;
	const std::string& name;
public:
	NameNode(const logging::Location& loc, const std::string& name);
	virtual ~NameNode();
	virtual const logging::Location& location();
	const std::string& getName();
};

class CallNode : public ExprNode
{
public:
	CallNode();
	virtual ~CallNode(){};
};

class ArrayNode : public ExprNode
{
public:
	ArrayNode();
	virtual ~ArrayNode(){};
	void append(const ExprNode* node);
};

class AbstractAssignNode : public ExprNode
{
protected:
	AbstractAssignNode(){};
	virtual ~AbstractAssignNode(){};
public:
};

class AssignNode : public AbstractAssignNode
{
	AssignNode();
	virtual ~AssignNode();
public:
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class OpAssignNode : public AbstractAssignNode
{
	OpAssignNode();
	virtual ~OpAssignNode();
public:
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class LiteralNode : public ExprNode
{
private:
	const logging::Location loc;
public:
	LiteralNode(const logging::Location& loc) :loc(loc) {};
	virtual ~LiteralNode(){};
	virtual const logging::Location& location();
};

class StringLiteralNode : public LiteralNode
{
private:
	const std::string literal;
public:
	StringLiteralNode(const logging::Location& loc, const std::string& literal);
	virtual ~StringLiteralNode(){};

	const std::string& getLiteral();
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class IntegerLiteralNode : public LiteralNode
{
private:
	const int literal;
public:
	IntegerLiteralNode(const logging::Location& loc, const int literal);
	virtual ~IntegerLiteralNode(){};
	const int getLiteral();
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

class BoolLiteralNode : public LiteralNode
{
private:
	const bool literal;
public:
	BoolLiteralNode(const logging::Location& loc, const bool literal);
	virtual ~BoolLiteralNode(){};
	const bool getLiteral();
//	virtual void accept(machine::NodeWalker& walker){walker.walk(this);};
};

} /* namespace tree */
#endif /* NODE_H_ */
