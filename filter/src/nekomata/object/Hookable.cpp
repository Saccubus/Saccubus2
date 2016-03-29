/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "../machine/Machine.h"
#include "Object.h"
#include <cinamo/String.h>

namespace nekomata{
namespace object{

HookableObject::HookableObject(Object& parent)
:Object(parent, 0)
{
	ADD_BUILTIN(clone);
	includeBuitin();
}
HookableObject::HookableObject(HookableObject& parent, int hash)
:Object(parent, hash)
{
	this->getterList.insert(parent.getterList.begin(),parent.getterList.end());
	this->setterList.insert(parent.setterList.begin(),parent.setterList.end());
}

void HookableObject::addGetter(std::string const& name, Getter getter)
{
	this->getterList.insert(std::pair<std::string, Getter>(name, getter));
}
void HookableObject::addSetter(std::string const& name, Setter setter)
{
	this->setterList.insert(std::pair<std::string, Setter>(name, setter));
}


Handler<Object> HookableObject::setSlot(std::string const& key, const Handler<Object> value)
{
	if(setterList.count(key) > 0){
		setterList.at(key)(self().cast<HookableObject>(), getHeap(), value);
		return value;
	}else{
		return Object::setSlot(key, value);
	}
}
Handler<Object> HookableObject::getSlot(std::string const& key)
{
	if(getterList.count(key) > 0){
		return getterList.at(key)(this->self().cast<HookableObject>(), getHeap());
	}else{
		return Object::getSlot(key);
	}
}
bool HookableObject::has(std::string const& key)
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

std::string HookableObject::toString()
{
	return cinamo::format("<<HookableObject:%d>>", getHash());
}

DEF_BUILTIN(HookableObject, clone)
{
	const Handler<HookableObject> self(machine.getSelf().cast<HookableObject>());
	return machine.pushResult( self->getHeap().newUndefinedObject() );
}


}}
