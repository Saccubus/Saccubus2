/*
 * Heap.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include "../logging/Logging.h"
#include <cstdarg>
#include <math.h>
#include <set>
#include <algorithm>
#include <tr1/functional>

namespace nekomata{
namespace object{

const static std::string TAG("HEAP");

ObjectHeap::ObjectHeap(logging::Logger& log, machine::System& system, GarbageCollectionCallback& callback)
:callback(callback)
,log(log)
,from(&area1)
,to(&area2)
,count(0)
,lastObjectSize(50)
,gcCount(0)
,topLevelObject(*this, system)
,rawObject(*this, true)
,baseObject(*this, false)
,baseLambdaObject(*this)
,baseLambdaScopeObject(*this)
,baseStringObject(baseObject)
,baseNumericObject(baseObject)
,trueObject(baseObject, true)
,falseObject(baseObject, false)
,undefinedObject(*this)
{
}
ObjectHeap::~ObjectHeap()
{
	for(std::vector<Object*>::iterator it = from->begin();it!=from->begin();++it)
	{
		delete *it;
	}
}

TopLevelObject* ObjectHeap::getTopLevelObject()
{
	return &topLevelObject;
}

Object* ObjectHeap::newObject()
{
	Object* obj = new Object(baseObject, createHash());
	registObject(obj);
	return obj;
}

Object* ObjectHeap::newRawObject()
{
	Object* obj = new Object(rawObject, createHash());
	registObject(obj);
	return obj;
}
LambdaScopeObject* ObjectHeap::newLambdaScopeObject(Object* const arg)
{
	LambdaScopeObject* obj = new LambdaScopeObject(baseLambdaScopeObject, createHash(), arg);
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
	StringObject* obj = new StringObject(baseStringObject, createHash(), str);
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
	NumericObject* obj = new NumericObject(baseNumericObject, createHash(), num);
	registObject(obj);
	return obj;
}

UndefinedObject* ObjectHeap::newUndefinedObject()
{
	return &undefinedObject;
}

LazyEvalObject* ObjectHeap::newLazyEvalObject(machine::Machine& machine, const tree::ObjectNode *objNode)
{
	LazyEvalObject* obj = new LazyEvalObject(baseObject, createHash(), machine, objNode);
	registObject(obj);
	return obj;
}

MethodNodeObject* ObjectHeap::newMethodNodeObject(Object* const scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule, std::vector<std::string>& argList)
{
	MethodNodeObject* obj = new MethodNodeObject(rawObject, createHash(), scope, node, rule, argList);
	registObject(obj);
	return obj;
}
MethodNodeObject* ObjectHeap::newMethodNodeObject(Object* const scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule)
{
	MethodNodeObject* obj = new MethodNodeObject(rawObject, createHash(), scope, node, rule);
	registObject(obj);
	return obj;
}

LambdaObject* ObjectHeap::newLambdaObject(Object* const scope, const tree::Node* node)
{
	LambdaObject* const obj = new LambdaObject(baseLambdaObject, createHash(), scope, node);
	registObject(obj);
	return obj;
}

bool deleteFunc(int color, std::set<Object*, std::tr1::function<bool(Object*, Object*)> >* unused, Object* obj)
{
	if(obj->getColor() == color){
		return false;
	}else{
		unused->insert(obj);
		return true;
	}
}

void ObjectHeap::checkGC()
{
	if(from->size() > lastObjectSize){
		this->callback.needGC(*this);
		lastObjectSize = from->size()*2;
	}
}

void ObjectHeap::gc(std::vector<Object*>& root)
{
	gcCount++;
	size_t before = this->from->size();

	for(std::vector<Object*>::const_iterator it=root.begin();it!=root.end();++it)
	{
		(*it)->mark(this->gcCount);
	}
	std::set<Object*> unused;
	for(std::vector<Object*>::const_iterator it=from->begin();it!=from->end();++it)
	{
		if((*it)->getColor() != gcCount){
			unused.insert(*it);
		}else{
			to->push_back(*it);
		}
	}

	log.d(TAG, 0, "Garbage collected: %d objects from %d objects", unused.size(), before);
	for(std::set<Object*>::const_iterator it=unused.begin();it!=unused.end();++it)
	{
		delete (*it);
	}

	this->from->clear();
	std::swap(from, to);
}

int ObjectHeap::createHash()
{
	return ++count;
}

}
}
