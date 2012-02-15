/*
 * Undefined.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include <math.h>
#include "Object.h"
#include "Heap.h"

namespace machine{
UndefinedObject::UndefinedObject(ObjectHeap& heap, const unsigned int hash)
:Object(heap, hash)
{

}
UndefinedObject::~UndefinedObject()
{

}
StringObject* UndefinedObject::toStringObject()
{
	return getHeap().newStringObject("undefined");
}
NumericObject* UndefinedObject::toNumericObject()
{
	return getHeap().newNumericObject(NAN);
}
BooleanObject* UndefinedObject::toBooleanObject()
{
	return getHeap().newBooleanObject(false);
}
bool UndefinedObject::isUndefined(){
	return true;
}

}

