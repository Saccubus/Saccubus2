/*
 * Numeric.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */

#include "../machine/Machine.h"
#include "Object.h"
#include "Heap.h"
#include <sstream>
#include <math.h>
#include <stdlib.h>

namespace nekomata{
namespace object{

const double NumericObject::EPSILON = 1e-10;

NumericObject::NumericObject(Object& parent)
:LiteralObject(parent), value(NAN)
{
	ADD_BUILTIN(plus);
	ADD_BUILTIN(minus);
	ADD_BUILTIN(increase);
	ADD_BUILTIN(decrease);
	ADD_BUILTIN(add);
	ADD_BUILTIN(subtract);
	ADD_BUILTIN(multiply);
	ADD_BUILTIN(divide);
	ADD_BUILTIN(modulo);

	ADD_BUILTIN(equals);
	ADD_BUILTIN(notEquals);
	ADD_BUILTIN(notLessThan);
	ADD_BUILTIN(notGreaterThan);
	ADD_BUILTIN(greaterThan);
	ADD_BUILTIN(lessThan);


	ADD_BUILTIN(floor);
	ADD_BUILTIN(sin);
	ADD_BUILTIN(cos);
	ADD_BUILTIN(pow);
	includeBuitin();
}
NumericObject::NumericObject(NumericObject& parent, int hash, const double literal)
: LiteralObject(parent,hash), value(literal)
{
}
NumericObject::~NumericObject()
{
}
StringObject* NumericObject::toStringObject()
{
	std::stringstream ss;
	double r = round(value);
	if(fabs(value-r) < EPSILON){
		ss << static_cast<int>(r);
	}else{
		ss << value;
	}
	return getHeap().newStringObject(ss.str());
}
NumericObject* NumericObject::toNumericObject()
{
	return this;
}
BooleanObject* NumericObject::toBooleanObject()
{
	return getHeap().newBooleanObject(fabs(value) < EPSILON);
}
double NumericObject::toNumeric(){
	return value;
}
void NumericObject::_method_plus(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(fabs(self->toNumeric())));
}
void NumericObject::_method_minus(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(-1*fabs(self->toNumeric())));
}
void NumericObject::_method_increase(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+1));
}
void NumericObject::_method_decrease(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-1));
}
void NumericObject::_method_add(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+other->toNumeric()));
}
void NumericObject::_method_subtract(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-other->toNumeric()));
}
void NumericObject::_method_multiply(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()*other->toNumeric()));
}
void NumericObject::_method_divide(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()/other->toNumeric()));
}
void NumericObject::_method_modulo(NativeMethodObject* method, machine::Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(static_cast<long>(self->toNumeric())%static_cast<long>(other->toNumeric())));
}
void NumericObject::_method_clone(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
}

void NumericObject::_method_equals(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject( fabs(self->toNumeric()-other->toNumeric()) < EPSILON ) );
}
void NumericObject::_method_notEquals(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject( fabs(self->toNumeric()-other->toNumeric()) >= EPSILON ) );
}
void NumericObject::_method_notLessThan(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric()-other->toNumeric() >= EPSILON) );
}
void NumericObject::_method_notGreaterThan(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() <= -EPSILON) );
}
void NumericObject::_method_greaterThan(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() > EPSILON) );
}
void NumericObject::_method_lessThan(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() < EPSILON) );
}
void NumericObject::_method_floor(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( floor(self->toNumeric()) ) );
}
void NumericObject::_method_sin(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( sin(self->toNumeric()) ) );
}
void NumericObject::_method_cos(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( cos(self->toNumeric()) ) );
}
void NumericObject::_method_pow(NativeMethodObject* method, machine::Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( pow(self->toNumeric(), other->toNumeric()) ) );
}


}
}
