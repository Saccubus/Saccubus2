/*
 * Undefined.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include <cmath>
#include "../classdefs.h"
#include "Object.h"
#include "Heap.h"

namespace nekomata{
namespace object{
UndefinedObject::UndefinedObject(ObjectHeap& heap)
:Object(heap)
{

}
UndefinedObject::~UndefinedObject()
{

}
std::string UndefinedObject::toString()
{
	return "undefined";
}
double UndefinedObject::toNumeric()
{
	return NAN;
}
bool UndefinedObject::toBool()
{
	return false;
}
bool UndefinedObject::isUndefined(){
	return true;
}

}
}

