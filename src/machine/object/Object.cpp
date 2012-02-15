/*
 * Object.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "../Machine.h"
#include <math.h>
#include <sstream>

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
Object* Object::index(size_t idx)
{
	if(objectList.size() > idx){
		return objectList.at(idx);
	}else{
		return getHeap().newUndefinedObject();
	}
}

bool Object::isUndefined(){
	return false;
}

Object* Object::setSlot(const std::string& name, Object* const item)
{
	MapIterator it = objectMap.find(name);
	Object* original;
	if(it == objectMap.end()){
		original = getHeap().newUndefinedObject();
	}else{
		original = it->second;
	}
	objectMap.insert(MapPair(name, item));
	return original;
}
Object* Object::getSlot(const std::string& name){
	MapIterator it = objectMap.find(name);
	return it == objectMap.end() ? getHeap().newUndefinedObject() : it->second;
}

StringObject* Object::toStringObject()
{
	std::stringstream ss;
	ss << "Object: " << getHash();
	return getHeap().newStringObject(ss.str());
}
NumericObject* Object::toNumericObject()
{
	return getHeap().newNumericObject(NAN);
}
BooleanObject* Object::toBooleanObject()
{
	return getHeap().newBooleanObject(true);
}

void Object::inject(Object* to){
	to->objectList.insert(to->objectList.end(), objectList.begin(), objectList.end());
	to->objectMap.insert(objectMap.begin(), objectMap.end());
}

void Object::_method_def(NativeMethodObject* method, Machine& machine)
{

}
void Object::_method_def_kari(NativeMethodObject* method, Machine& machine)
{

}
void Object::_method_setSlot(NativeMethodObject* method, Machine& machine)
{

}
void Object::_method_getSlot(NativeMethodObject* method, Machine& machine)
{
}
void Object::_method_clone(NativeMethodObject* method, Machine& machine){
}

}
 /* namespace machine */
