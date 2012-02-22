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
#include <set>
#include <algorithm>
#include <tr1/functional>

namespace nekomata{
namespace machine{

const static std::string TAG("HEAP");

ObjectHeap::ObjectHeap(logging::Logger& log, GarbageCollectionCallback& callback)
:callback(callback)
,log(log)
,from(&area1)
,to(&area2)
,count(0)
,lastObjectSize(50)
,gcCount(0)
,trueObject(*this, 0, true)
,falseObject(*this, 0, false)
,undefinedObject(*this, 0)
{
	setWorld();
}

void ObjectHeap::injectMethods(Object* const obj, std::map<std::string, NativeMethodObject>& methods)
{
	typedef std::map<std::string, NativeMethodObject>::iterator _it;
	for(_it it = methods.begin(); it!=methods.end();++it){
		obj->setSlot(it->first, &it->second);
	}
}

void ObjectHeap::setWorld()
{
	typedef std::pair<std::string, NativeMethodObject> _pair;
	{
		rawObjectBuiltinMethod.insert(_pair("getSlot", NativeMethodObject(*this, 0, Object::_method_getSlot)));
		rawObjectBuiltinMethod.insert(_pair("setSlot", NativeMethodObject(*this, 0, Object::_method_setSlot)));
	}
	{
		baseObjectBuiltinMethod.insert(_pair("def", NativeMethodObject(*this, 0, Object::_method_def)));
		baseObjectBuiltinMethod.insert(_pair("def_kari", NativeMethodObject(*this, 0, Object::_method_def_kari)));
		baseObjectBuiltinMethod.insert(_pair("index", NativeMethodObject(*this, 0, Object::_method_index)));
		baseObjectBuiltinMethod.insert(_pair("indexSet", NativeMethodObject(*this, 0, Object::_method_indexSet)));
		baseObjectBuiltinMethod.insert(_pair("size", NativeMethodObject(*this, 0, Object::_method_size)));
		baseObjectBuiltinMethod.insert(_pair("unshift", NativeMethodObject(*this, 0, Object::_method_unshift)));
		baseObjectBuiltinMethod.insert(_pair("push", NativeMethodObject(*this, 0, Object::_method_push)));
		baseObjectBuiltinMethod.insert(_pair("shift", NativeMethodObject(*this, 0, Object::_method_shift)));
		baseObjectBuiltinMethod.insert(_pair("pop", NativeMethodObject(*this, 0, Object::_method_pop)));
		baseObjectBuiltinMethod.insert(_pair("sort", NativeMethodObject(*this, 0, Object::_method_sort)));
		baseObjectBuiltinMethod.insert(_pair("sum", NativeMethodObject(*this, 0, Object::_method_sum)));
		baseObjectBuiltinMethod.insert(_pair("product", NativeMethodObject(*this, 0, Object::_method_product)));
		baseObjectBuiltinMethod.insert(_pair("join", NativeMethodObject(*this, 0, Object::_method_join)));
		baseObjectBuiltinMethod.insert(_pair("clone", NativeMethodObject(*this, 0, Object::_method_clone)));
		//
		baseObjectBuiltinMethod.insert(_pair("if", NativeMethodObject(*this, 0, Object::_method_if)));
		baseObjectBuiltinMethod.insert(_pair("while_kari", NativeMethodObject(*this, 0, Object::_method_while_kari)));
		baseObjectBuiltinMethod.insert(_pair("lambda", NativeMethodObject(*this, 0, Object::_method_lambda)));

		baseObjectBuiltinMethod.insert(_pair("rand", NativeMethodObject(*this, 0, Object::_method_rand)));
		baseObjectBuiltinMethod.insert(_pair("distance", NativeMethodObject(*this, 0, Object::_method_distance)));
	}
	{
		baseLambdaObjectBuiltinMethod.insert(_pair("index", NativeMethodObject(*this, 0, LambdaObject::_method_index)));
		baseLambdaScopeObjectBuiltinMethod.insert(_pair("@", NativeMethodObject(*this, 0, LambdaScopeObject::_method_atmark)));
	}
	{
		baseNumericObjectBuiltinMethod.insert(_pair("plus", NativeMethodObject(*this, 0, NumericObject::_method_plus)));
		baseNumericObjectBuiltinMethod.insert(_pair("minus", NativeMethodObject(*this, 0, NumericObject::_method_minus)));
		baseNumericObjectBuiltinMethod.insert(_pair("increase", NativeMethodObject(*this, 0, NumericObject::_method_increase)));
		baseNumericObjectBuiltinMethod.insert(_pair("decrease", NativeMethodObject(*this, 0, NumericObject::_method_decrease)));
		baseNumericObjectBuiltinMethod.insert(_pair("add", NativeMethodObject(*this, 0, NumericObject::_method_add)));
		baseNumericObjectBuiltinMethod.insert(_pair("subtract", NativeMethodObject(*this, 0, NumericObject::_method_subtract)));
		baseNumericObjectBuiltinMethod.insert(_pair("multiply", NativeMethodObject(*this, 0, NumericObject::_method_multiply)));
		baseNumericObjectBuiltinMethod.insert(_pair("divide", NativeMethodObject(*this, 0, NumericObject::_method_divide)));
		baseNumericObjectBuiltinMethod.insert(_pair("modulo", NativeMethodObject(*this, 0, NumericObject::_method_modulo)));
		//
		baseNumericObjectBuiltinMethod.insert(_pair("equals", NativeMethodObject(*this, 0, NumericObject::_method_equals)));
		baseNumericObjectBuiltinMethod.insert(_pair("notEquals", NativeMethodObject(*this, 0, NumericObject::_method_notEquals)));
		baseNumericObjectBuiltinMethod.insert(_pair("notLessThan", NativeMethodObject(*this, 0, NumericObject::_method_notLessThan)));
		baseNumericObjectBuiltinMethod.insert(_pair("notGreaterThan", NativeMethodObject(*this, 0, NumericObject::_method_notGreaterThan)));
		baseNumericObjectBuiltinMethod.insert(_pair("greaterThan", NativeMethodObject(*this, 0, NumericObject::_method_greaterThan)));
		baseNumericObjectBuiltinMethod.insert(_pair("lessThan", NativeMethodObject(*this, 0, NumericObject::_method_lessThan)));


		baseNumericObjectBuiltinMethod.insert(_pair("floor", NativeMethodObject(*this, 0, NumericObject::_method_floor)));
		baseNumericObjectBuiltinMethod.insert(_pair("sin", NativeMethodObject(*this, 0, NumericObject::_method_sin)));
		baseNumericObjectBuiltinMethod.insert(_pair("cos", NativeMethodObject(*this, 0, NumericObject::_method_cos)));
		baseNumericObjectBuiltinMethod.insert(_pair("pow", NativeMethodObject(*this, 0, NumericObject::_method_pow)));
	}
	{
		baseStringObjectBuiltinMethod.insert(_pair("equals", NativeMethodObject(*this, 0, StringObject::_method_equals)));
		baseStringObjectBuiltinMethod.insert(_pair("notEquals", NativeMethodObject(*this, 0, StringObject::_method_notEquals)));
		baseStringObjectBuiltinMethod.insert(_pair("notLessThan", NativeMethodObject(*this, 0, StringObject::_method_notLessThan)));
		baseStringObjectBuiltinMethod.insert(_pair("notGreaterThan", NativeMethodObject(*this, 0, StringObject::_method_notGreaterThan)));
		baseStringObjectBuiltinMethod.insert(_pair("greaterThan", NativeMethodObject(*this, 0, StringObject::_method_greaterThan)));
		baseStringObjectBuiltinMethod.insert(_pair("lessThan", NativeMethodObject(*this, 0, StringObject::_method_lessThan)));

		baseStringObjectBuiltinMethod.insert(_pair("index", NativeMethodObject(*this, 0, StringObject::_method_index)));
		baseStringObjectBuiltinMethod.insert(_pair("size", NativeMethodObject(*this, 0, StringObject::_method_size)));
		baseStringObjectBuiltinMethod.insert(_pair("indexOf", NativeMethodObject(*this, 0, StringObject::_method_indexOf)));
		baseStringObjectBuiltinMethod.insert(_pair("slice", NativeMethodObject(*this, 0, StringObject::_method_slice)));
		baseStringObjectBuiltinMethod.insert(_pair("toInteger", NativeMethodObject(*this, 0, StringObject::_method_toInteger)));
		baseStringObjectBuiltinMethod.insert(_pair("toFloat", NativeMethodObject(*this, 0, StringObject::_method_toFloat)));
		baseStringObjectBuiltinMethod.insert(_pair("eval", NativeMethodObject(*this, 0, StringObject::_method_eval)));

		baseStringObjectBuiltinMethod.insert(_pair("add", NativeMethodObject(*this, 0, StringObject::_method_add)));
	}
	{
		baseBooleanObjectBuiltinMethod.insert(_pair("or", NativeMethodObject(*this, 0, BooleanObject::_method_or)));
		baseBooleanObjectBuiltinMethod.insert(_pair("not", NativeMethodObject(*this, 0, BooleanObject::_method_not)));
		baseBooleanObjectBuiltinMethod.insert(_pair("and", NativeMethodObject(*this, 0, BooleanObject::_method_and)));
		baseBooleanObjectBuiltinMethod.insert(_pair("alternate", NativeMethodObject(*this, 0, BooleanObject::_method_alternate)));
		baseBooleanObjectBuiltinMethod.insert(_pair("alt", NativeMethodObject(*this, 0, BooleanObject::_method_alternate)));
		injectMethods(&trueObject, rawObjectBuiltinMethod);
		injectMethods(&trueObject, baseObjectBuiltinMethod);
		injectMethods(&trueObject, baseBooleanObjectBuiltinMethod);
		injectMethods(&falseObject, rawObjectBuiltinMethod);
		injectMethods(&falseObject, baseObjectBuiltinMethod);
		injectMethods(&falseObject, baseBooleanObjectBuiltinMethod);
	}
}

ObjectHeap::~ObjectHeap()
{
	for(std::vector<Object*>::iterator it = from->begin();it!=from->begin();++it)
	{
		delete *it;
	}
}

Object* ObjectHeap::newObject()
{
	Object* obj = new Object(*this, createHash());
	injectMethods(obj, rawObjectBuiltinMethod);
	injectMethods(obj, baseObjectBuiltinMethod);
	registObject(obj);
	return obj;
}

Object* ObjectHeap::newRawObject()
{
	Object* obj = new Object(*this, createHash());
	injectMethods(obj, rawObjectBuiltinMethod);
	registObject(obj);
	return obj;
}
LambdaScopeObject* ObjectHeap::newLambdaScopeObject(Object* const arg)
{
	LambdaScopeObject* obj = new LambdaScopeObject(*this, createHash(), arg);
	injectMethods(obj, baseLambdaScopeObjectBuiltinMethod);
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
	injectMethods(obj, rawObjectBuiltinMethod);
	injectMethods(obj, baseObjectBuiltinMethod);
	injectMethods(obj, baseStringObjectBuiltinMethod);
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
	injectMethods(obj, rawObjectBuiltinMethod);
	injectMethods(obj, baseObjectBuiltinMethod);
	injectMethods(obj, baseNumericObjectBuiltinMethod);
	registObject(obj);
	return obj;
}

UndefinedObject* ObjectHeap::newUndefinedObject()
{
	return &undefinedObject;
}

LazyEvalObject* ObjectHeap::newLazyEvalObject(Machine& machine, const tree::ObjectNode *objNode)
{
	LazyEvalObject* const obj = new LazyEvalObject(*this, createHash(), machine, objNode);
	registObject(obj);
	return obj;
}

MethodNodeObject* ObjectHeap::newMethodNodeObject(Object* const scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule, std::vector<std::string>& argList)
{
	MethodNodeObject* const obj = new MethodNodeObject(*this, createHash(), scope, node, rule, argList);
	registObject(obj);
	return obj;
}
MethodNodeObject* ObjectHeap::newMethodNodeObject(Object* const scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule)
{
	MethodNodeObject* const obj = new MethodNodeObject(*this, createHash(), scope, node, rule);
	registObject(obj);
	return obj;
}

LambdaObject* ObjectHeap::newLambdaObject(Object* const scope, const tree::Node* node)
{
	LambdaObject* const obj = new LambdaObject(*this, createHash(), scope, node);
	injectMethods(obj, baseLambdaObjectBuiltinMethod);
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
