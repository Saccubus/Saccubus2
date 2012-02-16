/*
 * Boolean.cpp
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
}


