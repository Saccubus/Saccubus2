/*
 * String.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */

#include "../Machine.h"
#include "Object.h"
#include "Heap.h"
#include <sstream>
#include <math.h>
#include <stdlib.h>

namespace machine{

StringObject::StringObject(ObjectHeap& heap, const unsigned int hash, const std::string& value)
:LiteralObject(heap, hash), value(value)
{

}
StringObject::~StringObject()
{

}
StringObject* StringObject::toStringObject()
{
	return this;
}
NumericObject* StringObject::toNumericObject()
{
	double val = strtol(this->value.c_str(), 0, 0);
	return getHeap().newNumericObject(val);
}
BooleanObject* StringObject::toBooleanObject()
{
	return getHeap().newBooleanObject(value.size() > 0);
}
const std::string& StringObject::toString()
{
	return value;
}

void StringObject::_method_equals(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() == other->toString() ) );
}
void StringObject::_method_notEquals(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() != other->toString() ) );
}
void StringObject::_method_notLessThan(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() >= other->toString() ) );
}
void StringObject::_method_notGreaterThan(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() <= other->toString() ) );
}
void StringObject::_method_greaterThan(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() > other->toString() ) );
}
void StringObject::_method_lessThan(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() < other->toString() ) );
}
void StringObject::_method_index(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
}
void StringObject::_method_size(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
}
void StringObject::_method_indexOf(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
}
void StringObject::_method_slice(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
}
void StringObject::_method_toInteger(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
}
void StringObject::_method_toFloat(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
}
void StringObject::_method_eval(NativeMethodObject* method, Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	//FIXME:
}


}

