/*
 * Object.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "../Machine.h"

namespace machine
{

Object::Object(ObjectHeap& heap, const unsigned int hash)
:heap(heap), hash(hash)
{
	// TODO Auto-generated constructor stub

}

Object::~Object()
{
	// TODO Auto-generated destructor stub
}

void Object::eval(Machine& machine){
	machine.pushReturnValue(this);
}

int Object::push(Object* const item)
{
	objectList.push_back(item);
	return objectList.size();
}

bool Object::isUndefined(){
	return false;
}

Object* Object::setSlot(const std::string& name, Object* const item)
{
	return 0;
}
Object* Object::getSlot(const std::string& name){
	return 0;
}

}
 /* namespace machine */
