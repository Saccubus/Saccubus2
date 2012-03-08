/*
 * NativeMethod.cpp
 *
 *  Created on: 2012/02/27
 *      Author: psi
 */

#include <cmath>
#include <sstream>
#include <algorithm>
#include <tr1/functional>
#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include "../util/StringUtil.h"

namespace nekomata{
namespace object
{
NativeMethodObject::NativeMethodObject(ObjectHeap& heap, Method method)
:MethodObject(heap), method(method){

}
NativeMethodObject::~NativeMethodObject()
{

}
void NativeMethodObject::eval(machine::Machine& machine)
{
	method(this, machine);
}

std::string NativeMethodObject::toString()
{
	return util::format("<< NathiveMethodObject %d >>", getHash());
}


}}
