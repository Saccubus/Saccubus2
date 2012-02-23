/*
 * Boolean.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include <sstream>
#include <math.h>
#include <stdlib.h>

namespace nekomata{
namespace object{

BooleanObject::BooleanObject(ObjectHeap& heap, const unsigned int hash, const bool value)
:LiteralObject(heap,hash), value(value)
{

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

void BooleanObject::_method_and(NativeMethodObject* method, machine::Machine& machine)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	BooleanObject* const other = machine.getArgument()->index(0)->toBooleanObject();
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() && other->toBool()));
}
void BooleanObject::_method_or(NativeMethodObject* method, machine::Machine& machine)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	BooleanObject* const other = machine.getArgument()->index(0)->toBooleanObject();
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() || other->toBool()));
}
void BooleanObject::_method_not(NativeMethodObject* method, machine::Machine& machine)
{
	BooleanObject* const self = machine.getSelf()->toBooleanObject();
	machine.pushResult(self->getHeap().newBooleanObject(!self->toBool()));
}
void BooleanObject::_method_alternate(NativeMethodObject* method, machine::Machine& machine)
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
