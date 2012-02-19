/*
 * Object.h
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#ifndef MACHINE_OBJECT_H_
#define MACHINE_OBJECT_H_

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include "../classdef.h"
#include "../../tree/Node.h"

namespace machine
{

class Object
{
private:
	ObjectHeap& heap;
	const int hash;
	std::vector<Object*> objectList;
	std::map<std::string, Object*> objectMap;
	typedef std::vector<Object*>::iterator Iterator;
	typedef std::map<std::string, Object*>::iterator MapIterator;
	typedef std::pair<std::string, Object*> MapPair;
protected:
	ObjectHeap& getHeap(){return heap;};
public:
	Object(ObjectHeap& heap, const unsigned int hash);
	virtual ~Object();
	unsigned int getHash(){return hash;};
public:
	virtual void inject(Object* to);
public: /* INDEXアクセス */
	virtual Object* unshift(Object* const item);
	virtual Object* push(Object* const item);
	virtual Object* shift();
	virtual Object* pop();
	virtual Object* index(size_t idx);
	virtual Object* indexSet(size_t idx, Object* item);
	virtual size_t size();
	virtual bool has(size_t idx);
public: /* KEYアクセス */
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public: /* 基本操作 */
	virtual bool isUndefined();
	virtual void eval(Machine& machine);
	virtual StringObject* toStringObject();
	virtual NumericObject* toNumericObject();
	virtual BooleanObject* toBooleanObject();
private:
	static bool _sort_func(Machine& machine, Object* const self, Object* const other);
public:
	static void _method_def(NativeMethodObject* method, Machine& machine);
	static void _method_def_kari(NativeMethodObject* method, Machine& machine);

	static void _method_index(NativeMethodObject* method, Machine& machine);
	static void _method_indexSet(NativeMethodObject* method, Machine& machine);
	static void _method_size(NativeMethodObject* method, Machine& machine);
	static void _method_unshift(NativeMethodObject* method, Machine& machine);
	static void _method_push(NativeMethodObject* method, Machine& machine);
	static void _method_shift(NativeMethodObject* method, Machine& machine);
	static void _method_pop(NativeMethodObject* method, Machine& machine);
	static void _method_sort(NativeMethodObject* method, Machine& machine);
	static void _method_sum(NativeMethodObject* method, Machine& machine);
	static void _method_product(NativeMethodObject* method, Machine& machine);
	static void _method_join(NativeMethodObject* method, Machine& machine);

	static void _method_setSlot(NativeMethodObject* method, Machine& machine);
	static void _method_getSlot(NativeMethodObject* method, Machine& machine);
	static void _method_clone(NativeMethodObject* method, Machine& machine);
public:
	static void _method_if(NativeMethodObject* method, Machine& machine);
	static void _method_while_kari(NativeMethodObject* method, Machine& machine);
	static void _method_lambda(NativeMethodObject* method, Machine& machine);
};

//-----------------------------------------------------------------------------

class LazyEvalObject : public Object
{
private:
	Machine& machine;
	const tree::ObjectNode* const node;
	std::map<std::string, bool> slotEvalState;
	std::map<size_t, bool> indexEvalState;
public:
	LazyEvalObject(ObjectHeap& heap, const unsigned int hash, Machine& machine, const tree::ObjectNode* const node);
	virtual ~LazyEvalObject();
public: /* INDEXアクセス */
	virtual Object* unshift(Object* const item);
	virtual Object* push(Object* const item);
	virtual Object* shift();
	virtual Object* pop();
	virtual Object* index(size_t idx);
	virtual Object* indexSet(size_t idx, Object* item);
	virtual size_t size();
	virtual bool has(size_t idx);
public: /* KEYアクセス */
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public:
	const tree::ObjectNode* const getRawNode() const{return node;};
};
class MethodObject : public Object{
protected:
	MethodObject(ObjectHeap& heap, const unsigned int hash):Object(heap,hash){};
	virtual ~MethodObject(){}
};

class NativeMethodObject : public MethodObject
{
public:
	typedef void (*Method)(NativeMethodObject* method, Machine& machine);
private:
	const Method method;
public:
	NativeMethodObject(ObjectHeap& heap, const unsigned int hash, Method method):MethodObject(heap,hash), method(method){};
	virtual ~NativeMethodObject(){};
	virtual void eval(Machine& machine){method(this, machine);}
};
class MethodNodeObject : public MethodObject
{
public:
	enum LocalScopeRule{
			def_kari,
			def
	};
private:
	const tree::Node* const node;
	const std::vector<std::string> argList;
	const LocalScopeRule rule;
	void mergeArg(Machine& machine, Object* const local, Object* const arg);
public:
	MethodNodeObject(ObjectHeap& heap, const unsigned int hash, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList);
	MethodNodeObject(ObjectHeap& heap, const unsigned int hash, const tree::Node* const node, LocalScopeRule rule);
	virtual ~MethodNodeObject();
	virtual void eval(Machine& machine);
};

//-----------------------------------------------------------------------------

class LiteralObject : public Object
{
protected:
	LiteralObject(ObjectHeap& heap, const unsigned int hash):Object(heap,hash){};
	~LiteralObject(){};
};
class StringObject : public LiteralObject
{
private:
	const std::string value;
public:
	StringObject(ObjectHeap& heap, const unsigned int hash, const std::string& value);
	~StringObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	const std::string& toString();
public:
	static void _method_equals(NativeMethodObject* method, Machine& machine);
	static void _method_notEquals(NativeMethodObject* method, Machine& machine);
	static void _method_notLessThan(NativeMethodObject* method, Machine& machine);
	static void _method_notGreaterThan(NativeMethodObject* method, Machine& machine);
	static void _method_greaterThan(NativeMethodObject* method, Machine& machine);
	static void _method_lessThan(NativeMethodObject* method, Machine& machine);
public:
	static void _method_index(NativeMethodObject* method, Machine& machine);
	static void _method_size(NativeMethodObject* method, Machine& machine);
	static void _method_indexOf(NativeMethodObject* method, Machine& machine);
	static void _method_slice(NativeMethodObject* method, Machine& machine);
	static void _method_toInteger(NativeMethodObject* method, Machine& machine);
	static void _method_toFloat(NativeMethodObject* method, Machine& machine);
	static void _method_eval(NativeMethodObject* method, Machine& machine);
public:
	static void _method_add(NativeMethodObject* method, Machine& machine);
};
class BooleanObject : public LiteralObject
{
private:
	const bool value;
public:
	BooleanObject(ObjectHeap& heap, const unsigned int hash, const bool value);
	~BooleanObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	bool toBool();
public:
	static void _method_and(NativeMethodObject* method, Machine& machine);
	static void _method_or(NativeMethodObject* method, Machine& machine);
	static void _method_not(NativeMethodObject* method, Machine& machine);
	static void _method_alternate(NativeMethodObject* method, Machine& machine);
};
class NumericObject : public LiteralObject
{
private:
	const double value;
public:
	const static double EPSILON;
	NumericObject(ObjectHeap& heap, const unsigned int hash, const double value);
	~NumericObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	double toNumeric();
public:
	static void _method_plus(NativeMethodObject* method, Machine& machine);
	static void _method_minus(NativeMethodObject* method, Machine& machine);
	static void _method_increase(NativeMethodObject* method, Machine& machine);
	static void _method_decrease(NativeMethodObject* method, Machine& machine);
	static void _method_add(NativeMethodObject* method, Machine& machine);
	static void _method_subtract(NativeMethodObject* method, Machine& machine);
	static void _method_multiply(NativeMethodObject* method, Machine& machine);
	static void _method_divide(NativeMethodObject* method, Machine& machine);
	static void _method_modulo(NativeMethodObject* method, Machine& machine);
	static void _method_clone(NativeMethodObject* method, Machine& machine);
public:
	static void _method_equals(NativeMethodObject* method, Machine& machine);
	static void _method_notEquals(NativeMethodObject* method, Machine& machine);
	static void _method_notLessThan(NativeMethodObject* method, Machine& machine);
	static void _method_notGreaterThan(NativeMethodObject* method, Machine& machine);
	static void _method_greaterThan(NativeMethodObject* method, Machine& machine);
	static void _method_lessThan(NativeMethodObject* method, Machine& machine);
public:
	static void _method_floor(NativeMethodObject* method, Machine& machine);
	static void _method_sin(NativeMethodObject* method, Machine& machine);
	static void _method_cos(NativeMethodObject* method, Machine& machine);
	static void _method_pow(NativeMethodObject* method, Machine& machine);

};

class UndefinedObject : public Object
{
public:
	UndefinedObject(ObjectHeap& heap, const unsigned int hash);
	~UndefinedObject();
public:
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	bool isUndefined();
};


} /* namespace machine */
#endif /* MACHINE_OBJECT_H_ */
