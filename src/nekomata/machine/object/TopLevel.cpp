/*
 * TopLevel.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include "../../Nekomata.h"
#include "../Machine.h"
#include "../System.h"
#include "Object.h"
#include "Heap.h"

namespace nekomata{
namespace machine{

#define ADD(name) \
		getterList.insert(GetterPair(#name, TopLevelObject::__getter__##name));\
		setterList.insert(SetterPair(#name, TopLevelObject::__setter__##name));


TopLevelObject::TopLevelObject(ObjectHeap& heap, const unsigned int hash, System& system):
	Object(heap, hash), system(system)
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
	return heap.newNumericObject(self.system.getCommentColor());
}
void TopLevelObject::__setter__commentColor(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setCommentColor(static_cast<unsigned int>(obj->index(0)->toNumericObject()->toNumeric()));
}
Object* TopLevelObject::__getter__commentPlace(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newStringObject(self.system.getCommentPlace());
}
void TopLevelObject::__setter__commentPlace(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setCommentPlace(obj->index(0)->toStringObject()->toString());
}
Object* TopLevelObject::__getter__commentSize(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newStringObject(self.system.getCommentSize());
}
void TopLevelObject::__setter__commentSize(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setCommentSize(obj->index(0)->toStringObject()->toString());
}
Object* TopLevelObject::__getter__commentInvisible(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getCommentInvisible());
}
void TopLevelObject::__setter__commentInvisible(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setCommentInvisible(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__commentReverse(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getCommentReverse());
}
void TopLevelObject::__setter__commentReverse(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setCommentReverse(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__defaultSage(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getDefaultSage());
}
void TopLevelObject::__setter__defaultSage(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setDefaultSage(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__postDisabled(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getPostDisabled());
}
void TopLevelObject::__setter__postDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setPostDisabled(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__seekDisabled(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getSeekDisabled());
}
void TopLevelObject::__setter__seekDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setSeekDisabled(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__isLoaded(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getIsLoaded());
}
void TopLevelObject::__setter__isLoaded(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setIsLoaded(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__isWide(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newBooleanObject(self.system.getIsWide());
}
void TopLevelObject::__setter__isWide(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setIsWide(obj->index(0)->toBooleanObject()->toBool());
}
Object* TopLevelObject::__getter__lastVideo(TopLevelObject& self, ObjectHeap& heap)
{
	return heap.newStringObject(self.system.getLastVideo());
}
void TopLevelObject::__setter__lastVideo(TopLevelObject& self, ObjectHeap& heap, Object* const obj)
{
	self.system.setLastVideo(obj->index(0)->toStringObject()->toString());
}

}
}

