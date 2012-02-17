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
	machine.pushResult(this);
}

int Object::push(Object* const item)
{
	objectList.push_back(item);
	return objectList.size();
}
Object* Object::getIndex(size_t idx)
{
	if(idx < objectList.size() && idx>=0){
		return objectList.at(idx);
	}else{
		return getHeap().newUndefinedObject();
	}
}
Object* Object::setIndex(size_t idx, Object* obj)
{
	if(idx < objectList.size()){
		objectList[idx] = obj;
	}else{
		objectList.insert(objectList.end(), objectList.size()-idx, getHeap().newUndefinedObject());
		objectList.push_back(obj);
	}
	return obj;
}
bool Object::hasIndex(size_t idx)
{
	return idx >= 0 && idx < objectList.size();
}
bool Object::hasSlot(const std::string& name)
{
	return objectMap.count(name) > 0;
}
std::vector<std::string> Object::getSlotNames()
{
	std::vector<std::string> slotList;
	for(MapIterator it = objectMap.begin(); it != objectMap.end(); ++it){
		slotList.push_back(it->first);
	}
	return slotList;
}

bool Object::isUndefined(){
	return false;
}
Object* Object::setSlot(const std::string& name, Object* const item)
{
	objectMap.erase(name);
	objectMap.insert(MapPair(name, item));
	return item;
}
Object* Object::getSlot(const std::string& name){
	MapIterator it = objectMap.find(name);
	return it == objectMap.end() ? getHeap().newUndefinedObject() : it->second;
}

StringObject* Object::toStringObject()
{
	std::stringstream ss;
	ss << "<< Object: " << getHash() << ">> {";
	for(MapIterator it = objectMap.begin();it != objectMap.end();++it){
		ss << std::endl << it->first << " : " << it->second->toStringObject()->toString();
	}
	int cnt=0;
	for(Iterator it = objectList.begin();it != objectList.end();++it){
		ss << std::endl << "$" << cnt << " : " << (*it)->toStringObject()->toString();
		++cnt;
	}
	ss << "}";
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
	Object* const arg = machine.getArgument();
	Object* const self = machine.getSelf();
	std::string name = arg->getIndex(0)->toStringObject()->toString();
	Object* const obj = arg->getIndex(1);
	machine.pushResult(self->setSlot(name, obj));
}
void Object::_method_getSlot(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	std::string name = machine.getArgument()->getIndex(0)->toStringObject()->toString();
	Object* const obj = self->getSlot(name);
	machine.pushResult(obj);
}
void Object::_method_clone(NativeMethodObject* method, Machine& machine){
}

}
 /* namespace machine */
