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
#include <cmath>
#include <cstdlib>

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
std::string NumericObject::toString()
{
	std::stringstream ss;
	double r = round(value);
	if(fabs(value-r) < EPSILON){
		ss << static_cast<int>(r);
	}else{
		ss << value;
	}
	return ss.str();
}
bool NumericObject::toBool()
{
	return value == 0;
}
double NumericObject::toNumeric(){
	return value;
}

DEF_BUILTIN(NumericObject, plus){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(fabs(self->toNumeric())));
}
DEF_BUILTIN(NumericObject, minus){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(-1*fabs(self->toNumeric())));
}
DEF_BUILTIN(NumericObject, increase){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+1));
}
DEF_BUILTIN(NumericObject, decrease){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-1));
}
DEF_BUILTIN(NumericObject, add){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+other->toNumeric()));
}
DEF_BUILTIN(NumericObject, subtract){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-other->toNumeric()));
}
DEF_BUILTIN(NumericObject, multiply){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()*other->toNumeric()));
}
DEF_BUILTIN(NumericObject, divide){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()/other->toNumeric()));
}
DEF_BUILTIN(NumericObject, modulo){
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult(self->getHeap().newNumericObject(static_cast<long>(self->toNumeric())%static_cast<long>(other->toNumeric())));
}
DEF_BUILTIN(NumericObject, clone)
{
	//FIXME: コピーできない？
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult(self->getHeap().newUndefinedObject());
}

DEF_BUILTIN(NumericObject, equals)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newBooleanObject( fabs(self->toNumeric()-other->toNumeric()) < EPSILON ) );
}
DEF_BUILTIN(NumericObject, notEquals)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newBooleanObject( fabs(self->toNumeric()-other->toNumeric()) >= EPSILON ) );
}
DEF_BUILTIN(NumericObject, notLessThan)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric()-other->toNumeric() >= EPSILON) );
}
DEF_BUILTIN(NumericObject, notGreaterThan)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() <= -EPSILON) );
}
DEF_BUILTIN(NumericObject, greaterThan)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() > EPSILON) );
}
DEF_BUILTIN(NumericObject, lessThan)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() - other->toNumeric() < EPSILON) );
}
DEF_BUILTIN(NumericObject, floor)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult( self->getHeap().newNumericObject( floor(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, sin)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult( self->getHeap().newNumericObject( sin(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, cos)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	machine.pushResult( self->getHeap().newNumericObject( cos(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, pow)
{
	NumericObject* const self = dynamic_cast<NumericObject*>(machine.getSelf());
	Object* const other = machine.getArgument()->index(0);
	machine.pushResult( self->getHeap().newNumericObject( pow(self->toNumeric(), other->toNumeric()) ) );
}


}
}
