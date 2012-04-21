/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../machine/Machine.h"
#include "Object.h"
#include "../util/StringUtil.h"

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


Handler<Object> HookableObject::setSlot(const std::string& key, const Handler<Object> value)
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

std::string HookableObject::toString()
{
	return util::format("<<HookableObject:%d>>", getHash());
}

DEF_BUILTIN(HookableObject, clone)
{
	const Handler<HookableObject> self(machine.getSelf());
	return machine.pushResult( self->getHeap().newUndefinedObject() );
}


}}
