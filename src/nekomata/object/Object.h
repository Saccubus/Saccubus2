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

#ifndef MACHINE_OBJECT_H_
#define MACHINE_OBJECT_H_

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include <nekomata/classdefs.h>
#include <nekomata/util/Handler.h>

namespace nekomata{
namespace object{

using util::Handler;

class Object
{
protected:
	Object();
private:
	Object(const Object& other);
	Object& operator=(const Object& other);
public:
	explicit Object(ObjectHeap& heap);
	explicit Object(ObjectHeap& heap, bool isRaw);
	explicit Object(Object& parent, const unsigned int hash);
	virtual ~Object();
public: /* Builtin Method Utils */
#define ADD_BUILTIN(name) \
		addBuiltin(#name, new NativeMethodObject(getHeap(), _method_##name));
#define ADD_BUILTIN_ALT(name, alt) \
		addBuiltin((alt), new NativeMethodObject(getHeap(), _method_##name));
#define DEC_BUILTIN(name) \
	static void _method_##name(NativeMethodObject* method, machine::Machine& machine);
#define DEF_BUILTIN(clazz, name) \
	void clazz::_method_##name(NativeMethodObject* method, machine::Machine& machine)

	typedef std::map<std::string, NativeMethodObject*> BuiltinMethods;
	typedef std::pair<std::string, NativeMethodObject*> BuiltinMethodPair;
protected:
	void addBuiltin(const std::string& name, NativeMethodObject* obj);
	void includeBuitin();
public: /* SlotTypeDefinition */
	typedef std::vector<Object*>::const_iterator SlotListIterator;
	typedef std::map<std::string, Object*>::const_iterator SlotMapIterator;
	typedef std::pair<std::string, Object*> SlotMapPair;
private: /* Heap management */
	ObjectHeap& heap;
	const int hash;
	int color;
	int nativeRef;
	BuiltinMethods* builtins;
	std::vector<Object*> objectList;
	std::map<std::string, Object*> objectMap;
	std::map<std::string, Object*> specialMap;
	bool _frozen;
protected:
	ObjectHeap& getHeap(){return heap;};
public:
	logging::Logger& log();
public:
	int getHash(){return hash;};
	void mark(int color);
	int getColor();
	int getNativeRef();
	void incNativeRef();
	void decNativeRef();
public: /* INDEXアクセス */
	virtual Handler<Object> unshift(const Handler<Object> item);
	virtual Handler<Object> push(const Handler<Object> item);
	virtual Handler<Object> shift();
	virtual Handler<Object> pop();
	virtual Handler<Object> index(size_t idx);
	virtual Handler<Object> indexSet(size_t idx, Handler<Object> item);
	virtual size_t size();
	virtual bool has(size_t idx);
public: /* KEYアクセス */
	virtual Handler<Object> setSlot(const std::string& key, const Handler<Object> value);
	virtual Handler<Object> getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public: /* 基本操作 */
	virtual void eval(machine::Machine& machine);
	virtual std::string toString();
	virtual double toNumeric();
	virtual bool toBool();
	virtual bool isUndefined();
	bool frozen();
	void freeze();
private:
	static bool _sort_func(machine::Machine* machine, Object* const self, Object* const other);
public:
	DEC_BUILTIN(def);
	DEC_BUILTIN(def_kari);

	DEC_BUILTIN(index);
	DEC_BUILTIN(indexSet);
	DEC_BUILTIN(size);
	DEC_BUILTIN(unshift);
	DEC_BUILTIN(push);
	DEC_BUILTIN(shift);
	DEC_BUILTIN(pop);
	DEC_BUILTIN(sort);
	DEC_BUILTIN(sum);
	DEC_BUILTIN(product);
	DEC_BUILTIN(join);

	DEC_BUILTIN(setSlot);
	DEC_BUILTIN(getSlot);
	DEC_BUILTIN(clone);

	DEC_BUILTIN(equals);
	DEC_BUILTIN(notEquals);
	DEC_BUILTIN(alternate);
public:
	DEC_BUILTIN(if);
	DEC_BUILTIN(while_kari);
	DEC_BUILTIN(lambda);
public:
	DEC_BUILTIN(distance);
	DEC_BUILTIN(rand);
};
//-----------------------------------------------------------------------------

class HookableObject : public Object
{
public:
	typedef Handler<Object> (*Getter)(Handler<HookableObject> self, ObjectHeap& heap);
	typedef void (*Setter)(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj);
	explicit HookableObject(Object& parent);
	explicit HookableObject(HookableObject& parent, int hash);
	virtual ~HookableObject();
#define ADD_HOOK_ACCESSOR(name) \
		addGetter(#name, _getter_##name);\
		addSetter(#name, _setter_##name);
#define DEC_HOOK_ACCESSOR(name) \
	static Handler<Object> _getter_##name(Handler<HookableObject> self, ObjectHeap& heap);\
	static void _setter_##name(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj);
#define DEF_HOOK_GETTER(clazz, name) \
	Handler<Object> clazz::_getter_##name(Handler<HookableObject> self, ObjectHeap& heap)
#define DEF_HOOK_SETTER(clazz, name) \
	void clazz::_setter_##name(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj)

#define DEF_HOOK_ACCESSOR_STR(clazz, name, adapter) \
	Handler<Object> clazz::_getter_##name(Handler<HookableObject> self, ObjectHeap& heap)\
	{\
		return heap.newStringObject(Handler<clazz>(self)->adapter->name());\
	}\
	void clazz::_setter_##name(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj)\
	{\
		Handler<clazz>(self)->adapter->name(obj->toString());\
	}

#define DEF_HOOK_ACCESSOR_DOUBLE(clazz, name, adapter) \
	Handler<Object> clazz::_getter_##name(Handler<HookableObject> self, ObjectHeap& heap)\
	{\
		return heap.newNumericObject(Handler<clazz>(self)->adapter->name());\
	}\
	void clazz::_setter_##name(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj)\
	{\
		Handler<clazz>(self)->adapter->name(obj->toNumeric());\
	}

#define DEF_HOOK_ACCESSOR_INT(clazz, name, adapter, type) \
	Handler<Object> clazz::_getter_##name(Handler<HookableObject> self, ObjectHeap& heap)\
	{\
		return heap.newNumericObject(Handler<clazz>(self)->adapter->name());\
	}\
	void clazz::_setter_##name(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj)\
	{\
		Handler<clazz>(self)->adapter->name(static_cast<type>(obj->toNumeric()));\
	}
#define DEF_HOOK_ACCESSOR_BOOL(clazz, name, adapter) \
	Handler<Object> clazz::_getter_##name(Handler<HookableObject> self, ObjectHeap& heap)\
	{\
		return heap.newBooleanObject(Handler<clazz>(self)->adapter->name());\
	}\
	void clazz::_setter_##name(Handler<HookableObject> self, ObjectHeap& heap, const Handler<Object> obj)\
	{\
		Handler<clazz>(self)->adapter->name(obj->toBool());\
	}

private:
	std::map<std::string, Getter> getterList;
	std::map<std::string, Setter> setterList;
protected:
	void addGetter(const std::string& name, Getter getter);
	void addSetter(const std::string& name, Setter setter);
public:
	virtual Handler<Object> setSlot(const std::string& key, const Handler<Object> value);
	virtual Handler<Object> getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
	virtual std::string toString();
public:
	DEC_BUILTIN(clone);
};


//-----------------------------------------------------------------------------

class LazyEvalObject : public Object
{
private:
	machine::Machine& machine;
	const tree::ObjectNode* const node;
	std::map<std::string, bool> slotEvalState;
	std::map<size_t, bool> indexEvalState;
private:
	Handler<Object> forceEvalNode(const tree::ExprNode* const node);
public:
	explicit LazyEvalObject(Object& parent);
	explicit LazyEvalObject(Object& parent, const unsigned int hash, machine::Machine& machine, const tree::ObjectNode* const node);
	virtual ~LazyEvalObject();
	Handler<Object> forceEval(size_t idx);
	Handler<Object> forceEval(const std::string& name);
public: /* INDEXアクセス */
	virtual Handler<Object> unshift(const Handler<Object> item);
	virtual Handler<Object> push(const Handler<Object> item);
	virtual Handler<Object> shift();
	virtual Handler<Object> pop();
	virtual Handler<Object> index(size_t idx);
	virtual Handler<Object> indexSet(size_t idx, Handler<Object> item);
	virtual size_t size();
	virtual bool has(size_t idx);
public: /* KEYアクセス */
	virtual Handler<Object> setSlot(const std::string& key, const Handler<Object> value);
	virtual Handler<Object> getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public:
	virtual std::string toString();
public:
	const tree::ObjectNode* const getRawNode() const{return node;};
public:
	DEC_BUILTIN(clone);
};

//---------------------------------------------------------------------------------------------------------------------

class MethodObject : public Object{
protected:
	MethodObject(ObjectHeap& heap):Object(heap){};
	MethodObject(Object& parent, const unsigned int hash):Object(parent, hash){};
	virtual ~MethodObject(){}
public:
	virtual std::string toString() = 0;
};

class NativeMethodObject : public MethodObject
{
public:
	typedef void (*Method)(NativeMethodObject* method, machine::Machine& machine);
private:
	const Method method;
public:
	explicit NativeMethodObject(ObjectHeap& heap, Method method);
	virtual ~NativeMethodObject();
	virtual void eval(machine::Machine& machine);
public:
	virtual std::string toString();
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
	void mergeArg(machine::Machine& machine, const Handler<Object> local, const Handler<Object> arg);
public:
	explicit MethodNodeObject(Object& parent, const unsigned int hash, const Handler<Object> scope, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList);
	explicit MethodNodeObject(Object& parent, const unsigned int hash, const Handler<Object> scope, const tree::Node* const node, LocalScopeRule rule);
	virtual ~MethodNodeObject();
	virtual void eval(machine::Machine& machine);
public:
	virtual std::string toString();
};

class LambdaObject : public MethodObject
{
private:
	const tree::Node* const node;
public:
	explicit LambdaObject(ObjectHeap& heap);
	explicit LambdaObject(LambdaObject& parent, const unsigned int hash, const Handler<Object> scope, const tree::Node* const node);
	virtual ~LambdaObject();
public:
	DEC_BUILTIN(index);
public:
	virtual std::string toString();
public:
	const tree::Node* getNode(){ return node; };
};

class LambdaScopeObject : public Object
{
public:
	explicit LambdaScopeObject(Object& parent);
	explicit LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, const Handler<Object> arg);
	virtual ~LambdaScopeObject();
public:
	DEC_BUILTIN(atmark);
public:
	virtual std::string toString();
};

//---------------------------------------------------------------------------------------------------------------------

class LiteralObject : public Object
{
protected:
	explicit LiteralObject(Object& parent):Object(parent, 0){};
	explicit LiteralObject(LiteralObject& parent, int hash):Object(parent, hash){};
	virtual ~LiteralObject(){};
public:
	virtual std::string toString() = 0;
};
class StringObject : public LiteralObject
{
private:
	const std::string value;
private:
	const std::string& getValue();
public:
	explicit StringObject(Object& parent);
	explicit StringObject(StringObject& parent, int hash, const std::string& literal);
	virtual ~StringObject();
	virtual std::string toString();
	virtual double toNumeric();
	virtual bool toBool();
public:
	DEC_BUILTIN(equals);
	DEC_BUILTIN(notEquals);
	DEC_BUILTIN(notLessThan);
	DEC_BUILTIN(notGreaterThan);
	DEC_BUILTIN(greaterThan);
	DEC_BUILTIN(lessThan);
public:
	DEC_BUILTIN(index);
	DEC_BUILTIN(size);
	DEC_BUILTIN(indexOf);
	DEC_BUILTIN(slice);
	DEC_BUILTIN(toInteger);
	DEC_BUILTIN(toFloat);
	DEC_BUILTIN(eval);
public:
	DEC_BUILTIN(add);
	DEC_BUILTIN(multiply);
	DEC_BUILTIN(clone);
};
class BooleanObject : public LiteralObject
{
private:
	const bool value;
public:
	explicit BooleanObject(Object& parent, bool literal);
	virtual ~BooleanObject();
	virtual std::string toString();
	virtual double toNumeric();
	virtual bool toBool();
public:
	DEC_BUILTIN(and);
	DEC_BUILTIN(or);
	DEC_BUILTIN(not);
	DEC_BUILTIN(alternate);
	DEC_BUILTIN(clone);
};
class NumericObject : public LiteralObject
{
private:
	const double value;
public:
	const static double EPSILON;
	explicit NumericObject(Object& parent);
	explicit NumericObject(NumericObject& parent, int hash, const double literal);
	virtual ~NumericObject();
	virtual std::string toString();
	virtual double toNumeric();
	virtual bool toBool();
public:
	DEC_BUILTIN(plus);
	DEC_BUILTIN(minus);
	DEC_BUILTIN(increase);
	DEC_BUILTIN(decrease);
	DEC_BUILTIN(add);
	DEC_BUILTIN(subtract);
	DEC_BUILTIN(multiply);
	DEC_BUILTIN(divide);
	DEC_BUILTIN(modulo);
	DEC_BUILTIN(clone);
public:
	DEC_BUILTIN(compare);
	DEC_BUILTIN(equals);
	DEC_BUILTIN(notEquals);
	DEC_BUILTIN(notLessThan);
	DEC_BUILTIN(notGreaterThan);
	DEC_BUILTIN(greaterThan);
	DEC_BUILTIN(lessThan);
public:
	DEC_BUILTIN(floor);
	DEC_BUILTIN(sin);
	DEC_BUILTIN(cos);
	DEC_BUILTIN(pow);
public:
	DEC_BUILTIN(times);

};

class UndefinedObject : public Object
{
public:
	explicit UndefinedObject(Object& parent);
	virtual ~UndefinedObject();
public:
	virtual std::string toString();
	virtual double toNumeric();
	virtual bool toBool();
	bool isUndefined();
};

}}
#endif /* MACHINE_OBJECT_H_ */
