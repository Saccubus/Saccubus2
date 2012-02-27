/*
 * String.cpp
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
#include <unicode/unistr.h>

namespace nekomata{
namespace object{

StringObject::StringObject(Object& parent)
:LiteralObject(parent), value("null")
{
	ADD_BUILTIN(equals);
	ADD_BUILTIN(notEquals);
	ADD_BUILTIN(notLessThan);
	ADD_BUILTIN(notGreaterThan);
	ADD_BUILTIN(greaterThan);
	ADD_BUILTIN(lessThan);

	ADD_BUILTIN(index);
	ADD_BUILTIN(size);
	ADD_BUILTIN(indexOf);
	ADD_BUILTIN(slice);
	ADD_BUILTIN(toInteger);
	ADD_BUILTIN(toFloat);
	ADD_BUILTIN(eval);

	ADD_BUILTIN(add);
	includeBuitin();
}

StringObject::StringObject(StringObject& parent, int hash, const std::string& literal)
:LiteralObject(parent, hash), value(literal)
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

DEF_BUILTIN(StringObject, equals)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() == other->toString() ) );
}
DEF_BUILTIN(StringObject, notEquals)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() != other->toString() ) );
}
DEF_BUILTIN(StringObject, notLessThan)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() >= other->toString() ) );
}
DEF_BUILTIN(StringObject, notGreaterThan)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() <= other->toString() ) );
}
DEF_BUILTIN(StringObject, greaterThan)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() > other->toString() ) );
}
DEF_BUILTIN(StringObject, lessThan)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() < other->toString() ) );
}
DEF_BUILTIN(StringObject, index)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	Object* const arg = machine.getArgument();
	UnicodeString uni(self->value.c_str(), "utf-8");
	size_t idx = static_cast<size_t>(arg->index(0)->toNumericObject()->toNumeric());
	std::string result;
	uni.tempSubString(idx, 1).toUTF8String(result);
	machine.pushResult( self->getHeap().newStringObject(result) );
}
DEF_BUILTIN(StringObject, size)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	UnicodeString uni(self->value.c_str(), "utf-8");
	machine.pushResult( self->getHeap().newNumericObject(uni.length()) );
}
DEF_BUILTIN(StringObject, indexOf)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	Object* const arg = machine.getArgument();
	StringObject* const key = arg->index(0)->toStringObject();
	size_t from = 0;
	if(arg->size() > 1){
		from = static_cast<size_t>(arg->index(1)->toNumericObject()->toNumeric());
	}
	UnicodeString uni(self->value.c_str(), "utf-8");
	UnicodeString other(key->value.c_str(), "utf-8");
	machine.pushResult( self->getHeap().newNumericObject(uni.indexOf(other, from)) );
}
DEF_BUILTIN(StringObject, slice)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	UnicodeString uni(self->value.c_str(), "utf-8");
	Object* const arg = machine.getArgument();
	if(arg->size() <= 0){
		machine.pushResult(self);
	}else if(arg->size() == 1){
		UnicodeString uni(self->value.c_str(), "utf-8");
		int start=static_cast<int>(arg->index(0)->toNumericObject()->toNumeric());
		if(start < 0){
			start = uni.length()+start;
		}
		std::string result;
		uni.tempSubString(start).toUTF8String(result);
		machine.pushResult( self->getHeap().newStringObject(result) );
	}else{
		int start=static_cast<int>(arg->index(0)->toNumericObject()->toNumeric());
		if(start < 0){
			start = uni.length()+start;
		}
		const int limit=static_cast<int>(arg->index(1)->toNumericObject()->toNumeric());
		std::string result;
		uni.tempSubString(start, limit).toUTF8String(result);
		machine.pushResult( self->getHeap().newStringObject(result) );
	}
}
DEF_BUILTIN(StringObject, toInteger)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	char* ptr;
	const size_t len = self->toString().size();
	const char* str = self->toString().c_str();
	double num = strtol( str, &ptr, 0);
	if(ptr < &str[len]){
		machine.pushResult( self->getHeap().newNumericObject(NAN) );
	}else{
		machine.pushResult( self->getHeap().newNumericObject(num) );
	}
}
DEF_BUILTIN(StringObject, toFloat)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	char* ptr;
	const size_t len = self->toString().size();
	const char* str = self->toString().c_str();
	double num = strtod(str, &ptr);
	if(ptr < &str[len]){
		machine.pushResult( self->getHeap().newNumericObject(NAN) );
	}else{
		machine.pushResult( self->getHeap().newNumericObject(num) );
	}
}
DEF_BUILTIN(StringObject, eval)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	//FIXME:
}

DEF_BUILTIN(StringObject, add)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newStringObject(self->toString()+other->toString()) );

}


}
}
