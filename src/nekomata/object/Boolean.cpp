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
	ADD_BUILTIN(clone);
	includeBuitin();
	freeze();
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
	Handler<BooleanObject> self(machine.getSelf().cast<BooleanObject>());
	const bool other = cast<bool>(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() && other));
}
DEF_BUILTIN(BooleanObject, or)
{
	Handler<BooleanObject> self(machine.getSelf().cast<BooleanObject>());
	const bool other = cast<bool>(machine.getArgument()->index(0));
	machine.pushResult(self->getHeap().newBooleanObject(self->toBool() || other));
}
DEF_BUILTIN(BooleanObject, not)
{
	Handler<BooleanObject> self(machine.getSelf().cast<BooleanObject>());
	machine.pushResult(self->getHeap().newBooleanObject(!self->toBool()));
}
DEF_BUILTIN(BooleanObject, alternate)
{
	Handler<BooleanObject> self(machine.getSelf().cast<BooleanObject>());
	if(self->toBool()){
		machine.pushResult(machine.getArgument()->index(0));
	}else{
		machine.pushResult(machine.getArgument()->index(1));
	}
}

DEF_BUILTIN(BooleanObject, clone)
{
	Handler<BooleanObject> self(machine.getSelf().cast<BooleanObject>());
	machine.pushResult( self );
}

}}
