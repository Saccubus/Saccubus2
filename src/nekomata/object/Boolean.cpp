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
#include "Cast.h"
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
std::string BooleanObject::toString()
{
	if(value){
		return "true";
	}else{
		return "false";
	}
}
double BooleanObject::toNumeric()
{
	if(value){
		return 1;
	}else{
		return 0;
	}
}

bool BooleanObject::toBool()
{
	return value;
}

DEF_BUILTIN(BooleanObject, and)
{
	Handler<BooleanObject> self(machine.getSelf());
	const bool other = cast<bool>(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() && other));
}
DEF_BUILTIN(BooleanObject, or)
{
	Handler<BooleanObject> self(machine.getSelf());
	const bool other = cast<bool>(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() || other));
}
DEF_BUILTIN(BooleanObject, not)
{
	Handler<BooleanObject> self(machine.getSelf());
	machine.pushResult(self->getHeap().newBooleanObject(!self->toBool()));
}
DEF_BUILTIN(BooleanObject, alternate)
{
	Handler<BooleanObject> self(machine.getSelf());
	if(self->toBool()){
		machine.pushResult(machine.getArgument()->index(0));
	}else{
		machine.pushResult(machine.getArgument()->index(1));
	}
}


}
}
