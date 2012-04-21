/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

	ADD_BUILTIN(clone);
	includeBuitin();
	freeze();
}
NumericObject::NumericObject(NumericObject& parent, int hash, const double literal)
: LiteralObject(parent,hash), value(literal)
{
	freeze();
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
	return !(value != value);
}
double NumericObject::toNumeric(){
	return value;
}

DEF_BUILTIN(NumericObject, plus){
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(fabs(self->toNumeric())));
}
DEF_BUILTIN(NumericObject, minus){
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(-1*fabs(self->toNumeric())));
}
DEF_BUILTIN(NumericObject, increase){
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+1));
}
DEF_BUILTIN(NumericObject, decrease){
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-1));
}
DEF_BUILTIN(NumericObject, add){
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()+other->toNumeric()));
}
DEF_BUILTIN(NumericObject, subtract){
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()-other->toNumeric()));
}
DEF_BUILTIN(NumericObject, multiply){
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()*other->toNumeric()));
}
DEF_BUILTIN(NumericObject, divide){
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(self->toNumeric()/other->toNumeric()));
}
DEF_BUILTIN(NumericObject, modulo){
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newNumericObject(static_cast<long>(self->toNumeric())%static_cast<long>(other->toNumeric())));
}
DEF_BUILTIN(NumericObject, clone)
{
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject( self->toNumeric() ));
}

/* FIXME:見苦しすぎ */
static const double DELTA=1e-10;

DEF_BUILTIN(NumericObject, equals)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( std::fabs(self->toNumeric() - other->toNumeric()) < DELTA ) );
}
DEF_BUILTIN(NumericObject, notEquals)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( std::fabs(self->toNumeric() - other->toNumeric()) >= DELTA ) );
}
DEF_BUILTIN(NumericObject, notLessThan)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( (self->toNumeric() - other->toNumeric()) >= -DELTA ) );
}
DEF_BUILTIN(NumericObject, notGreaterThan)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( (self->toNumeric() - other->toNumeric()) <= DELTA ) );
}
DEF_BUILTIN(NumericObject, greaterThan)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() > other->toNumeric() ) );
}
DEF_BUILTIN(NumericObject, lessThan)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject(self->toNumeric() < other->toNumeric() ) );
}
DEF_BUILTIN(NumericObject, floor)
{
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult( self->getHeap().newNumericObject( floor(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, sin)
{
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult( self->getHeap().newNumericObject( sin(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, cos)
{
	const Handler<NumericObject> self(machine.getSelf());
	machine.pushResult( self->getHeap().newNumericObject( cos(self->toNumeric()) ) );
}
DEF_BUILTIN(NumericObject, pow)
{
	const Handler<NumericObject> self(machine.getSelf());
	const Handler<Object> other(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newNumericObject( pow(self->toNumeric(), other->toNumeric()) ) );
}


}}
