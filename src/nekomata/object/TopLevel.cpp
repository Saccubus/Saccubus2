/*
 * TopLevel.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include "../Nekomata.h"
#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../machine/System.h"

namespace nekomata{
namespace object{

#define ADD(name) \
		getterList.insert(GetterPair(#name, TopLevelObject::__getter__##name));\
		setterList.insert(SetterPair(#name, TopLevelObject::__setter__##name));


TopLevelObject::TopLevelObject(ObjectHeap& heap, machine::System& system):
	Object(heap), system(system)
{
	typedef std::pair<std::string, Getter> GetterPair;
	typedef std::pair<std::string, Setter> SetterPair;
	ADD(commentColor);
	ADD(commentPlace);
	ADD(commentSize);
	ADD(commentInvisible);
	ADD(commentReverse);
	ADD(defaultSage);
	ADD(postDisabled);
	ADD(seekDisabled);
	ADD(isLoaded);
	ADD(isWide);
	ADD(lastVideo);
}
TopLevelObject::~TopLevelObject()
{

}

Object* TopLevelObject::setSlot(const std::string& key, Object* const value)
{
	if(setterList.count(key) > 0){
		setterList.at(key)(*this, getHeap(), value);
		return value;
	}else{
		return Object::setSlot(key, value);
	}
}
Object* TopLevelObject::getSlot(const std::string& key)
{
	if(getterList.count(key) > 0){
		return getterList.at(key)(*this, getHeap());
	}else{
		return Object::getSlot(key);
	}
}
bool TopLevelObject::has(const std::string& key)
{
	return getterList.count(key) > 0 || Object::has(key);
}
std::vector<std::string> TopLevelObject::getSlotNames()
{
	std::vector<std::string> list = Object::getSlotNames();
	for(std::map<std::string, Getter>::iterator it = getterList.begin();it!=getterList.end();++it){
		list.push_back(it->first);
	}
	return list;
}
size_t TopLevelObject::slotSize()
{
	return Object::slotSize()+getterList.size();
}

//---------------------------------------------------------------------------------------------------------------------

Object* TopLevelObject::__getter__commentColor(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newNumericObject(self.system.commentColor());
}
void TopLevelObject::__setter__commentColor(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.commentColor(static_cast<unsigned int>(obj->index(0)->toNumericObject()->toNumeric()));
}
Object* TopLevelObject::__getter__commentPlace(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newStringObject(self.system.commentPlace());
}
void TopLevelObject::__setter__commentPlace(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.commentPlace(obj->index(0)->toStringObject()->toString());
}
Object* TopLevelObject::__getter__commentSize(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newStringObject(self.system.commentSize());
}
void TopLevelObject::__setter__commentSize(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.commentSize(obj->index(0)->toStringObject()->toString());
}
Object* TopLevelObject::__getter__commentInvisible(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.commentInvisible());
}
void TopLevelObject::__setter__commentInvisible(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.commentInvisible(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__commentReverse(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.commentReverse());
}
void TopLevelObject::__setter__commentReverse(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.commentReverse(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__defaultSage(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.defaultSage());
}
void TopLevelObject::__setter__defaultSage(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.defaultSage(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__postDisabled(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.postDisabled());
}
void TopLevelObject::__setter__postDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.postDisabled(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__seekDisabled(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.seekDisabled());
}
void TopLevelObject::__setter__seekDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.seekDisabled(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__isLoaded(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.isLoaded());
}
void TopLevelObject::__setter__isLoaded(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.isLoaded(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__isWide(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.isWide());
}
void TopLevelObject::__setter__isWide(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.isWide(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__lastVideo(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newStringObject(self.system.lastVideo());
}
void TopLevelObject::__setter__lastVideo(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.lastVideo(obj->index(0)->toStringObject()->toString());
}

}
}

