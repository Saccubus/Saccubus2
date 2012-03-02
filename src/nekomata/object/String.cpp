/*
 * String.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */

#include "Object.h"
#include "Cast.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <unicode/unistr.h>

namespace nekomata{
namespace object{

StringObject::StringObject(Object& parent)
:LiteralObject(parent), value("<null>")
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
double StringObject::toNumeric()
{
	double val = strtol(this->value.c_str(), 0, 0);
	return val;
}
bool StringObject::toBool()
{
	return value.size() > 0;
}
std::string StringObject::toString()
{
	return value;
}

const std::string& StringObject::getValue() /* toStringだと、std::stringオブジェクトがコピーされてしまう。 */
{
	return value;
}


DEF_BUILTIN(StringObject, equals)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( self->getValue() == other ) );
}
DEF_BUILTIN(StringObject, notEquals)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( self->getValue() != other ) );
}
DEF_BUILTIN(StringObject, notLessThan)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( self->getValue() >= other ) );
}
DEF_BUILTIN(StringObject, notGreaterThan)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( self->getValue() <= other ) );
}
DEF_BUILTIN(StringObject, greaterThan)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( self->getValue() > other ) );
}
DEF_BUILTIN(StringObject, lessThan)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newBooleanObject( self->getValue() < other ) );
}
DEF_BUILTIN(StringObject, index)
{
	const Handler<StringObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	UnicodeString uni(self->getValue().c_str(), "utf-8");
	size_t idx = cast<size_t>(arg->index(0));
	std::string result;
	uni.tempSubString(idx, 1).toUTF8String(result);
	machine.pushResult( self->getHeap().newStringObject(result) );
}
DEF_BUILTIN(StringObject, size)
{
	const Handler<StringObject> self(machine.getSelf());
	UnicodeString uni(self->getValue().c_str(), "utf-8");
	machine.pushResult( self->getHeap().newNumericObject(uni.length()) );
}
DEF_BUILTIN(StringObject, indexOf)
{
	const Handler<StringObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	std::string key = cast<std::string>(arg->index(0));
	size_t from = 0;
	if(arg->size() > 1){
		from = cast<size_t>(arg->index(1));
	}
	UnicodeString uni(self->getValue().c_str(), "utf-8");
	UnicodeString other(key.c_str(), "utf-8");
	machine.pushResult( self->getHeap().newNumericObject(uni.indexOf(other, from)) );
}
DEF_BUILTIN(StringObject, slice)
{
	const Handler<StringObject> self(machine.getSelf());
	UnicodeString uni(self->getValue().c_str(), "utf-8");
	const Handler<Object> arg(machine.getArgument());
	if(arg->size() <= 0){
		machine.pushResult(Handler<Object>(self));
	}else if(arg->size() == 1){
		UnicodeString uni(self->getValue().c_str(), "utf-8");
		int start=cast<int>(arg->index(0));
		if(start < 0){
			start = uni.length()+start;
		}
		std::string result;
		uni.tempSubString(start).toUTF8String(result);
		machine.pushResult( self->getHeap().newStringObject(result) );
	}else{
		int start=cast<int>(arg->index(0));
		if(start < 0){
			start = uni.length()+start;
		}
		const int limit=cast<int>(arg->index(1));
		std::string result;
		uni.tempSubString(start, limit).toUTF8String(result);
		machine.pushResult( self->getHeap().newStringObject(result) );
	}
}
DEF_BUILTIN(StringObject, toInteger)
{
	const Handler<StringObject> self(machine.getSelf());
	char* ptr;
	const size_t len = self->getValue().size();
	const char* str = self->getValue().c_str();
	double num = strtol( str, &ptr, 0);
	if(ptr < &str[len]){
		machine.pushResult( self->getHeap().newNumericObject(NAN) );
	}else{
		machine.pushResult( self->getHeap().newNumericObject(num) );
	}
}
DEF_BUILTIN(StringObject, toFloat)
{
	const Handler<StringObject> self(machine.getSelf());
	char* ptr;
	const size_t len = self->getValue().size();
	const char* str = self->getValue().c_str();
	double num = strtod(str, &ptr);
	if(ptr < &str[len]){
		machine.pushResult( self->getHeap().newNumericObject(NAN) );
	}else{
		machine.pushResult( self->getHeap().newNumericObject(num) );
	}
}
DEF_BUILTIN(StringObject, eval)
{
	const Handler<StringObject> self(machine.getSelf());
	//FIXME:
	machine.pushResult(self->getHeap().newUndefinedObject());
}

DEF_BUILTIN(StringObject, add)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string const other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newStringObject(self->getValue()+other) );

}


}
}
