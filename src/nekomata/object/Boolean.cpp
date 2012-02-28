/*
 * Boolean.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */

#include <cmath>
#include <cstdlib>
#include <sstream>
#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"

namespace nekomata{
namespace object{

BooleanObject::BooleanObject(Object& parent, bool literal)
:LiteralObject(parent), value(literal)
{
	ADD_BUILTIN(and);
	ADD_BUILTIN(or);
	ADD_BUILTIN(not);
	ADD_BUILTIN(alternate);
	ADD_BUILTIN_ALT(alternate, "alt");
	includeBuitin();
}
BooleanObject::~BooleanObject()
{
}
StringObject* BooleanObject::toStringObject()
{
	if(value){
		return getHeap().newStringObject("true");
	}else{
		return getHeap().newStringObject("false");
	}
}
NumericObject* BooleanObject::toNumericObject()
{
	if(value){
		return getHeap().newNumericObject(1);
	}else{
		return getHeap().newNumericObject(0);
	}
}
BooleanObject* BooleanObject::toBooleanObject()
{
	return this;
}

bool BooleanObject::toBool()
{
	return value;
}

DEF_BUILTIN(BooleanObject, and)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	BooleanObject* const other = machine.getArgument()->index(0)->toBooleanObject();
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() && other->toBool()));
}
DEF_BUILTIN(BooleanObject, or)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	BooleanObject* const other = machine.getArgument()->index(0)->toBooleanObject();
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() || other->toBool()));
}
DEF_BUILTIN(BooleanObject, not)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	machine.pushResult(self->getHeap().newBooleanObject(!self->toBool()));
}
DEF_BUILTIN(BooleanObject, alternate)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	if(self->toBool()){
		machine.pushResult(machine.getArgument()->index(0));
	}else{
		machine.pushResult(machine.getArgument()->index(1));
	}
}


}
}
