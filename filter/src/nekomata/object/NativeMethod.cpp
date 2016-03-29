/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <cmath>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cinamo/String.h>

#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"

namespace nekomata{
namespace object
{
NativeMethodObject::NativeMethodObject(ObjectHeap& heap, Method method)
:MethodObject(heap), method(method){

}
void NativeMethodObject::eval(machine::Machine& machine)
{
	method(this, machine);
}

std::string NativeMethodObject::toString()
{
	return cinamo::format("<<NathiveMethodObject:%d>>", getHash());
}


}}
