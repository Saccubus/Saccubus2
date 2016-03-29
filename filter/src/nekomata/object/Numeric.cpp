/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "../machine/Machine.h"
#include "Object.h"
#include "Heap.h"
#include <sstream>
#include <cmath>
#include <cstdlib>

namespace nekomata{
namespace object{

/* FIXME:見苦しすぎ */
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

	ADD_BUILTIN(compare);
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

	ADD_BUILTIN(times);

	ADD_BUILTIN(clone);
	includeBuitin();
	freeze();
}
NumericObject::NumericObject(NumericObject& parent, int hash, const double literal)
: LiteralObject(parent,hash), value(literal)
{
	freeze();
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
	return !(value != value);
}
double NumericObject::toNumeric(){
	return value;
}

DEF_BUILTIN(NumericObject, plus){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult(self->getHeap().newNumericObject( self->toNumeric() ));
}
DEF_BUILTIN(NumericObject, minus){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult(self->getHeap().newNumericObject(-1* self->toNumeric() ));
}
DEF_BUILTIN(NumericObject, increase){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+1));
}
DEF_BUILTIN(NumericObject, decrease){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-1));
}
DEF_BUILTIN(NumericObject, add){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+other->toNumeric()));
}
DEF_BUILTIN(NumericObject, subtract){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-other->toNumeric()));
}
DEF_BUILTIN(NumericObject, multiply){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()*other->toNumeric()));
}
DEF_BUILTIN(NumericObject, divide){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()/other->toNumeric()));
}
DEF_BUILTIN(NumericObject, modulo){
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	if(other->toNumeric() == 0.0 || other != other){
		machine.pushResult(self->getHeap().newNumericObject( NAN ) );
	}else{
		machine.pushResult(self->getHeap().newNumericObject( self->toNumeric() - static_cast<int>(self->toNumeric() / other->toNumeric())*other->toNumeric() ) );
	}
}
DEF_BUILTIN(NumericObject, clone)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult(self->getHeap().newNumericObject( self->toNumeric() ));
}

DEF_BUILTIN(NumericObject, compare)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	const bool eq = std::fabs(self->toNumeric() - other->toNumeric()) < NumericObject::EPSILON;
	if (eq) {
		machine.pushResult( self->getHeap().newNumericObject( 0 ) );
	}else if(self->toNumeric() < other->toNumeric()){
		machine.pushResult( self->getHeap().newNumericObject( -1 ) );
	}else{
		machine.pushResult( self->getHeap().newNumericObject( 1 ) );
	}
}

DEF_BUILTIN(NumericObject, equals)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( std::fabs(self->toNumeric() - other->toNumeric()) < NumericObject::EPSILON ) );
}
DEF_BUILTIN(NumericObject, notEquals)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( std::fabs(self->toNumeric() - other->toNumeric()) >= NumericObject::EPSILON ) );
}
DEF_BUILTIN(NumericObject, notLessThan)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( (self->toNumeric() - other->toNumeric()) >= -NumericObject::EPSILON ) );
}
DEF_BUILTIN(NumericObject, notGreaterThan)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( (self->toNumeric() - other->toNumeric()) <= NumericObject::EPSILON ) );
}
DEF_BUILTIN(NumericObject, greaterThan)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() > other->toNumeric() ) );
}
DEF_BUILTIN(NumericObject, lessThan)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() < other->toNumeric() ) );
}
DEF_BUILTIN(NumericObject, floor)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult( self->getHeap().newNumericObject( floor(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, sin)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult( self->getHeap().newNumericObject( sin(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, cos)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	machine.pushResult( self->getHeap().newNumericObject( cos(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, pow)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newNumericObject( pow(self->toNumeric(), other->toNumeric()) ) );
}

DEF_BUILTIN(NumericObject, times)
{
	const Handler<NumericObject> self(machine.getSelf().cast<NumericObject>());
	const Handler<Object> lambda(machine.getArgument()->index(0));
	const int cnt = static_cast<int>( self->toNumeric() );
	Handler<Object> val = self->getHeap().newUndefinedObject();
	for(int i=0; i<cnt; ++i){
		const Handler<Object> countObj = self->getHeap().newNumericObject(i);
		const Handler<Object> indexArg = self->getHeap().newArrayObject(1, countObj.get());
		val = machine.send(lambda, "index", indexArg);
	}
	machine.pushResult( val );
}


}}
