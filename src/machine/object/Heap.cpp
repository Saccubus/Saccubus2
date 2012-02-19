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
,count(0)
,rawObject(*this, 0)
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
		obj.setSlot(it->first, &it->second);
	}
}

void ObjectHeap::setWorld()
{
	typedef std::pair<std::string, NativeMethodObject> _pair;
	{
		rawObjectBuiltinMethod.insert(_pair("getSlot", NativeMethodObject(*this, 0, Object::_method_getSlot)));
		rawObjectBuiltinMethod.insert(_pair("setSlot", NativeMethodObject(*this, 0, Object::_method_setSlot)));
		injectMethods(rawObject, rawObjectBuiltinMethod);
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
		injectMethods(baseObject, rawObjectBuiltinMethod);
		injectMethods(baseObject, baseObjectBuiltinMethod);
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
		injectMethods(baseNumericObject, rawObjectBuiltinMethod);
		injectMethods(baseNumericObject, baseObjectBuiltinMethod);
		injectMethods(baseNumericObject, baseNumericObjectBuiltinMethod);
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

		injectMethods(baseStringObject, rawObjectBuiltinMethod);
		injectMethods(baseStringObject, baseObjectBuiltinMethod);
		injectMethods(baseStringObject, baseStringObjectBuiltinMethod);
	}
	{
		baseBooleanObjectBuiltinMethod.insert(_pair("or", NativeMethodObject(*this, 0, BooleanObject::_method_or)));
		baseBooleanObjectBuiltinMethod.insert(_pair("not", NativeMethodObject(*this, 0, BooleanObject::_method_not)));
		baseBooleanObjectBuiltinMethod.insert(_pair("and", NativeMethodObject(*this, 0, BooleanObject::_method_and)));
		baseBooleanObjectBuiltinMethod.insert(_pair("alternate", NativeMethodObject(*this, 0, BooleanObject::_method_alternate)));
		baseBooleanObjectBuiltinMethod.insert(_pair("alt", NativeMethodObject(*this, 0, BooleanObject::_method_alternate)));
		injectMethods(trueObject, rawObjectBuiltinMethod);
		injectMethods(trueObject, baseObjectBuiltinMethod);
		injectMethods(trueObject, baseBooleanObjectBuiltinMethod);
		injectMethods(falseObject, rawObjectBuiltinMethod);
		injectMethods(falseObject, baseObjectBuiltinMethod);
		injectMethods(falseObject, baseBooleanObjectBuiltinMethod);
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

Object* ObjectHeap::newRawObject()
{
	Object* obj = new Object(*this, createHash());
	rawObject.inject(obj);
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


void ObjectHeap::gc(const Object *global)
{
}

unsigned int ObjectHeap::createHash()
{
	return ++count;
}

}

