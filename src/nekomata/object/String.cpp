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

StringObject::StringObject(ObjectHeap& heap, const unsigned int hash, const std::string& value)
:LiteralObject(heap, hash), value(value)
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

void StringObject::_method_equals(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() == other->toString() ) );
}
void StringObject::_method_notEquals(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() != other->toString() ) );
}
void StringObject::_method_notLessThan(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() >= other->toString() ) );
}
void StringObject::_method_notGreaterThan(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() <= other->toString() ) );
}
void StringObject::_method_greaterThan(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() > other->toString() ) );
}
void StringObject::_method_lessThan(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newBooleanObject( self->toString() < other->toString() ) );
}
void StringObject::_method_index(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	Object* const arg = machine.getArgument();
	UnicodeString uni(self->value.c_str(), "utf-8");
	size_t idx = static_cast<size_t>(arg->index(0)->toNumericObject()->toNumeric());
	std::string result;
	uni.tempSubString(idx, 1).toUTF8String(result);
	machine.pushResult( self->getHeap().newStringObject(result) );
}
void StringObject::_method_size(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	UnicodeString uni(self->value.c_str(), "utf-8");
	machine.pushResult( self->getHeap().newNumericObject(uni.length()) );
}
void StringObject::_method_indexOf(NativeMethodObject* method, machine::Machine& machine)
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
void StringObject::_method_slice(NativeMethodObject* method, machine::Machine& machine)
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
void StringObject::_method_toInteger(NativeMethodObject* method, machine::Machine& machine)
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
void StringObject::_method_toFloat(NativeMethodObject* method, machine::Machine& machine)
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
void StringObject::_method_eval(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	//FIXME:
}

void StringObject::_method_add(NativeMethodObject* method, machine::Machine& machine)
{
	StringObject* const self = machine.getSelf()->toStringObject();
	StringObject* const other = machine.getArgument()->index(0)->toStringObject();
	machine.pushResult( self->getHeap().newStringObject(self->toString()+other->toString()) );

}


}
}
