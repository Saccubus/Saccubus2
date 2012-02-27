/*
 * NativeMethod.cpp
 *
 *  Created on: 2012/02/27
 *      Author: psi
 */

#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include <math.h>
#include <sstream>
#include <algorithm>
#include <tr1/functional>

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


}}
