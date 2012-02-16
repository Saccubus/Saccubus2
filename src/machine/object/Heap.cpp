/*
 * Heap.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include <cstdarg>
#include <math.h>
namespace machine{

ObjectHeap::ObjectHeap()
:from(&area1)
,to(&area2)
,baseObject(*this, 0)
,baseStringObject(*this, 0, "")
,baseNumericObject(*this, 0, NAN)
,trueObject(*this, 0, true)
,falseObject(*this, 0, false)
,undefinedObject(*this, 0)
{
	setWorld();
}

void ObjectHeap::injectMethods(Object& obj, std::map<std::string, NativeMethodObject>& methods)
{
	typedef std::map<std::string, NativeMethodObject>::iterator _it;
	for(_it it = methods.begin(); it!=methods.end();++it){
		baseObject.setSlot(it->first, &it->second);
	}
}

void ObjectHeap::setWorld()
{
	typedef std::pair<std::string, NativeMethodObject> _pair;
	{
		baseObjectBuiltinMethod.insert(_pair("def", NativeMethodObject(*this, 0, Object::_method_def)));
		baseObjectBuiltinMethod.insert(_pair("def_kari", NativeMethodObject(*this, 0, Object::_method_def_kari)));
		baseObjectBuiltinMethod.insert(_pair("getSlot", NativeMethodObject(*this, 0, Object::_method_getSlot)));
		baseObjectBuiltinMethod.insert(_pair("setSlot", NativeMethodObject(*this, 0, Object::_method_setSlot)));
		baseObjectBuiltinMethod.insert(_pair("clone", NativeMethodObject(*this, 0, Object::_method_clone)));
		injectMethods(baseObject, baseObjectBuiltinMethod);
	}
}

ObjectHeap::~ObjectHeap()
{

}

Object* ObjectHeap::newObject()
{
	Object* obj = new Object(*this, createHash());
	baseObject.inject(obj);
	registObject(obj);
	return obj;
}

void ObjectHeap::registObject(Object* obj){
	this->from->push_back(obj);
}

Object* ObjectHeap::newArray(Object* obj, ...)
{
	va_list list;
	va_start(list, obj);
	Object* const result = newObject();
	Object* item = obj;
	while(item !=0){
		result->push(item);
		item = va_arg(list, Object*);
	}
	va_end(list);
	return result;
}

StringObject* ObjectHeap::newStringObject(const std::string & str)
{
	StringObject* obj = new StringObject(*this, createHash(), str);
	baseStringObject.inject(obj);
	registObject(obj);
	return obj;
}



BooleanObject* ObjectHeap::newBooleanObject(const bool val)
{
	if(val){
		return &trueObject;
	}else{
		return &falseObject;
	}
}



NumericObject* ObjectHeap::newNumericObject(const double num)
{
	NumericObject* obj = new NumericObject(*this, createHash(), num);
	baseNumericObject.inject(obj);
	registObject(obj);
	return obj;
}

UndefinedObject* ObjectHeap::newUndefinedObject()
{
	return &undefinedObject;
}



LazyEvalNodeObject* ObjectHeap::newLazyEvalNodeObject(const tree::Node *node)
{
	return 0;
}

LazyEvalObject* ObjectHeap::newLazyEvalObject(const tree::ObjectNode *objNode)
{
	return 0;
}

void ObjectHeap::gc(const Object *global)
{
}

unsigned int ObjectHeap::createHash()
{
	return ++count;
}

}

