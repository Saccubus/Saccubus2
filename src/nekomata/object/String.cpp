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

#include <sstream>
#include <cmath>
#include <cstdlib>
#include <tr1/memory>
#include <unicode/unistr.h>
#include <nekomata/parser/Parser.h>

#include "Object.h"
#include "Cast.h"
#include "Heap.h"
#include "../machine/Machine.h"

#include "../tree/Node.h"

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
	std::tr1::shared_ptr<const tree::ExprNode> node = parser::Parser::fromString(self->toString())->parseProgram();
	const Handler<Object> result(machine.eval(node.get()));
	machine.pushResult(result);
}

DEF_BUILTIN(StringObject, add)
{
	const Handler<StringObject> self(machine.getSelf());
	std::string const other = cast<std::string>(machine.getArgument()->index(0));
	machine.pushResult( self->getHeap().newStringObject(self->getValue()+other) );

}


}}
