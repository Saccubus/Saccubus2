/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
namespace nekomata {

class Nekomata;

namespace logging {
class Dumpable;
class Dumper;
class Logger;
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
class LambdaScopeObject;

class SystemObject;

class LiteralObject;
class StringObject;
class BooleanObject;
class NumericObject;

class UndefinedObject;

}

namespace machine{
class Machine;
}

namespace system{
class System;
class Message;
class Comment;
class Script;
class Label;
class Replace;
class Sum;
class SumResult;
class Shape;
}

namespace tree {
class Location;

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
