/*
 * classdef.h
 *
 *  Created on: 2012/02/12
 *      Author: psi
 */

#ifndef MACHINE_CLASSDEF_H_
#define MACHINE_CLASSDEF_H_

namespace nekomata{
namespace machine
{

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

//-----------------------------------------------
class Machine;
class System;

};
};

#endif /* MACHINE_CLASSDEF_H_ */
