/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <cmath>
#include "Object.h"

namespace nekomata{
namespace object{
UndefinedObject::UndefinedObject(Object& parent)
:Object(parent, 0)
{
	freeze();
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

}}
