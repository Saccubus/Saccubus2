/*
 * String.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */

#include "../Machine.h"
#include "Object.h"
#include "Heap.h"
#include <sstream>
#include <math.h>
#include <stdlib.h>

namespace machine{

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

}

