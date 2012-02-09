/*
 * classdefs.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef CLASSDEFS_H_
#define CLASSDEFS_H_

namespace logging{
	class Dumpable;
	class Dumper;
	class Location;
};

namespace machine{
	class NodeWalker;
};

namespace tree{
	class Node;
	class BoolLiteralNode;
	class IntegerLiteralNode;
	class StringLiteralNode;
	class AssignNode;
	class OpAssignNode;
	class IndexAcessNode;
	class BindNode;
	class PostOpNode;
	class PreOpNode;
	class BinOpNode;
	class ObjectNode;
	class InvokeNode;
	class ContNode;
}

#endif /* CLASSDEFS_H_ */
