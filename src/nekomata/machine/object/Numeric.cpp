/*
 * Numeric.cpp
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

namespace nekomata{
namespace machine{

const double NumericObject::EPSILON = 1e-10;
NumericObject::NumericObject(ObjectHeap& heap, const unsigned int hash, const double value)
: LiteralObject(heap,hash), value(value)
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
void NumericObject::_method_plus(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(fabs(self->toNumeric())));
}
void NumericObject::_method_minus(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(-1*fabs(self->toNumeric())));
}
void NumericObject::_method_increase(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+1));
}
void NumericObject::_method_decrease(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-1));
}
void NumericObject::_method_add(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+other->toNumeric()));
}
void NumericObject::_method_subtract(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-other->toNumeric()));
}
void NumericObject::_method_multiply(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()*other->toNumeric()));
}
void NumericObject::_method_divide(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()/other->toNumeric()));
}
void NumericObject::_method_modulo(NativeMethodObject* method, Machine& machine){
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult(self->getHeap().newNumericObject(static_cast<long>(self->toNumeric())%static_cast<long>(other->toNumeric())));
}
void NumericObject::_method_clone(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const newObj = self->getHeap().newNumericObject(self->toNumeric());
	self->inject(newObj);
	machine.pushResult(newObj);
}

void NumericObject::_method_equals(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject( fabs(self->toNumeric()-other->toNumeric()) < EPSILON ) );
}
void NumericObject::_method_notEquals(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject( fabs(self->toNumeric()-other->toNumeric()) >= EPSILON ) );
}
void NumericObject::_method_notLessThan(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric()-other->toNumeric() >= EPSILON) );
}
void NumericObject::_method_notGreaterThan(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() <= -EPSILON) );
}
void NumericObject::_method_greaterThan(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() > EPSILON) );
}
void NumericObject::_method_lessThan(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() < EPSILON) );
}
void NumericObject::_method_floor(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( floor(self->toNumeric()) ) );
}
void NumericObject::_method_sin(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( sin(self->toNumeric()) ) );
}
void NumericObject::_method_cos(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( cos(self->toNumeric()) ) );
}
void NumericObject::_method_pow(NativeMethodObject* method, Machine& machine)
{
	NumericObject* const self = machine.getSelf()->toNumericObject();
	NumericObject* const other = machine.getArgument()->index(0)->toNumericObject();
	machine.pushResult( self->getHeap().newNumericObject( pow(self->toNumeric(), other->toNumeric()) ) );
}


}
}
