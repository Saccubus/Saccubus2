/*
 * classdefs.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef CLASSDEFS_H_
#define CLASSDEFS_H_

namespace nekomata {

class Nekomata;
class Adapter;
class ChatAdapter;

namespace logging {
class Dumpable;
class Dumper;
class Logger;
class Location;
class Exception;
}

namespace object {

class ObjectHeap;

class Object;

class LazyEvalObject;
class MethodObject;
class NativeMethodObject;
class MethodNodeObject;

class LambdaObject;
class SambdaScopeObject;

class TopLevelObject;

class LiteralObject;
class StringObject;
class BooleanObject;
class NumericObject;

class UndefinedObject;

}

namespace machine{
class Machine;
class System;
}

namespace tree {
class NodeWalker;

class Node;
class ExprNode;

class BoolLiteralNode;
class NumericLiteralNode;
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

}

#endif /* CLASSDEFS_H_ */
