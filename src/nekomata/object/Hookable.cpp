/*
 * Hookable.cpp
 *
 *  Created on: 2012/02/27
 *      Author: psi
 */

#include "Object.h"

namespace nekomata{
namespace object{

HookableObject::HookableObject(Object& parent)
:Object(parent, 0)
{

}
HookableObject::HookableObject(HookableObject& parent, int hash)
:Object(parent, hash)
{
	this->getterList.insert(parent.getterList.begin(),parent.getterList.end());
	this->setterList.insert(parent.setterList.begin(),parent.setterList.end());
}

HookableObject::~HookableObject()
{

}

void HookableObject::addGetter(const std::string& name, Getter getter)
{
	this->getterList.insert(std::pair<std::string, Getter>(name, getter));
}
void HookableObject::addSetter(const std::string& name, Setter setter)
{
	this->setterList.insert(std::pair<std::string, Setter>(name, setter));
}


Handler<Object> HookableObject::setSlot(const std::string& key, Handler<Object> const value)
{
	if(setterList.count(key) > 0){
		setterList.at(key)(Handler<HookableObject>(this), getHeap(), value);
		return value;
	}else{
		return Object::setSlot(key, value);
	}
}
Handler<Object> HookableObject::getSlot(const std::string& key)
{
	if(getterList.count(key) > 0){
		return getterList.at(key)(Handler<HookableObject>(this), getHeap());
	}else{
		return Object::getSlot(key);
	}
}
bool HookableObject::has(const std::string& key)
{
	return getterList.count(key) > 0 || Object::has(key);
}
std::vector<std::string> HookableObject::getSlotNames()
{
	std::vector<std::string> list = Object::getSlotNames();
	for(std::map<std::string, Getter>::iterator it = getterList.begin();it!=getterList.end();++it){
		list.push_back(it->first);
	}
	return list;
}
size_t HookableObject::slotSize()
{
	return Object::slotSize()+getterList.size();
}

}}
