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
#include "../classdefs.h"

namespace nekomata{
namespace object{

class Object
{
public:
	explicit Object(ObjectHeap& heap);
	explicit Object(ObjectHeap& heap, bool isRaw);
	explicit Object(Object& parent, const unsigned int hash);
	virtual ~Object();
public: /* Builtin Method Utils */
#define ADD_BUILTIN(name) \
		addBuiltin(#name, NativeMethodObject(getHeap(), _method_##name));
#define ADD_BUILTIN_ALT(name, func) \
		addBuiltin((name), NativeMethodObject(getHeap(), _method_##func));
#define DEC_BUILTIN(name) \
	static void _method_##name(NativeMethodObject* method, machine::Machine& machine);

	typedef std::map<std::string, NativeMethodObject> BuiltinMethods;
	typedef std::pair<std::string, NativeMethodObject> BuiltinMethodPair;
protected:
	void addBuiltin(const std::string& name, NativeMethodObject obj);
	void includeBuitin();
public: /* SlotTypeDefinition */
	typedef std::vector<Object*>::iterator SlotListIterator;
	typedef std::map<std::string, Object*>::iterator SlotMapIterator;
	typedef std::pair<std::string, Object*> SlotMapPair;
private: /* Heap management */
	ObjectHeap& heap;
	const int hash;
	int color;
	BuiltinMethods* builtins;
	std::vector<Object*> objectList;
	std::map<std::string, Object*> objectMap;
protected:
	ObjectHeap& getHeap(){return heap;};
public:
	unsigned int getHash(){return hash;};
	void mark(int color);
	int getColor();
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
	virtual void eval(machine::Machine& machine);
	virtual StringObject* toStringObject();
	virtual NumericObject* toNumericObject();
	virtual BooleanObject* toBooleanObject();
private:
	static bool _sort_func(machine::Machine& machine, Object* const self, Object* const other);
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
public:
	DEC_BUILTIN(if);
	DEC_BUILTIN(while_kari);
	DEC_BUILTIN(lambda);
public:
	DEC_BUILTIN(distance);
	DEC_BUILTIN(rand);
};
//-----------------------------------------------------------------------------

class TopLevelObject : public Object
{
private:
	typedef Object* (*Getter)(TopLevelObject& self, ObjectHeap& heap);
	typedef void (*Setter)(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	std::map<std::string, Getter> getterList;
	std::map<std::string, Setter> setterList;
	machine::System& system;
public:
	explicit TopLevelObject(ObjectHeap& heap, machine::System& system);
	virtual ~TopLevelObject();
public:
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public:
	static Object* __getter__commentColor(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentColor(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentPlace(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentPlace(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentSize(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentSize(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentInvisible(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentInvisible(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentReverse(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentReverse(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__defaultSage(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__defaultSage(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__postDisabled(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__postDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__seekDisabled(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__seekDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__isLoaded(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__isLoaded(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__isWide(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__isWide(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__lastVideo(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__lastVideo(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
public:

};

//-----------------------------------------------------------------------------

class LazyEvalObject : public Object
{
private:
	machine::Machine& machine;
	const tree::ObjectNode* const node;
	std::map<std::string, bool> slotEvalState;
	std::map<size_t, bool> indexEvalState;
public:
	explicit LazyEvalObject(Object& parent, const unsigned int hash, machine::Machine& machine, const tree::ObjectNode* const node);
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

//---------------------------------------------------------------------------------------------------------------------

class MethodObject : public Object{
protected:
	MethodObject(ObjectHeap& heap):Object(heap){};
	MethodObject(Object& parent, const unsigned int hash):Object(parent, hash){};
	virtual ~MethodObject(){}
};

class NativeMethodObject : public MethodObject
{
public:
	typedef void (*Method)(NativeMethodObject* method, machine::Machine& machine);
private:
	const Method method;
public:
	explicit NativeMethodObject(ObjectHeap& heap, Method method):MethodObject(heap), method(method){};
	virtual ~NativeMethodObject(){};
	virtual void eval(machine::Machine& machine){method(this, machine);}
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
	void mergeArg(machine::Machine& machine, Object* const local, Object* const arg);
public:
	explicit MethodNodeObject(Object& parent, const unsigned int hash, Object* const scope, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList);
	explicit MethodNodeObject(Object& parent, const unsigned int hash, Object* const scope, const tree::Node* const node, LocalScopeRule rule);
	virtual ~MethodNodeObject();
	virtual void eval(machine::Machine& machine);
};

class LambdaObject : public MethodObject
{
private:
	const tree::Node* const node;
public:
	explicit LambdaObject(ObjectHeap& heap);
	explicit LambdaObject(LambdaObject& parent, const unsigned int hash, Object* const scope, const tree::Node* const node);
	virtual ~LambdaObject();
public:
	DEC_BUILTIN(index);
};

class LambdaScopeObject : public Object
{
public:
	explicit LambdaScopeObject(ObjectHeap& heap);
	explicit LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, Object* const arg);
	virtual ~LambdaScopeObject();
public:
	DEC_BUILTIN(atmark);
};

//---------------------------------------------------------------------------------------------------------------------

class LiteralObject : public Object
{
protected:
	explicit LiteralObject(Object& parent):Object(parent, 0){};
	explicit LiteralObject(LiteralObject& parent, int hash):Object(parent, hash){};
	virtual ~LiteralObject(){};
};
class StringObject : public LiteralObject
{
private:
	const std::string value;
public:
	explicit StringObject(Object& parent);
	explicit StringObject(StringObject& parent, int hash, const std::string& literal);
	virtual ~StringObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	const std::string& toString();
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
};
class BooleanObject : public LiteralObject
{
private:
	const bool value;
public:
	explicit BooleanObject(Object& parent, bool literal);
	virtual ~BooleanObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	bool toBool();
public:
	DEC_BUILTIN(and);
	DEC_BUILTIN(or);
	DEC_BUILTIN(not);
	DEC_BUILTIN(alternate);
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
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	double toNumeric();
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

};

class UndefinedObject : public Object
{
public:
	explicit UndefinedObject(ObjectHeap& heap);
	virtual ~UndefinedObject();
public:
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	bool isUndefined();
};


}
}
#endif /* MACHINE_OBJECT_H_ */
