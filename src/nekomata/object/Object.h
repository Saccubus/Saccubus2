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
#define ADD_BUILTIN_ALT(name, alt) \
		addBuiltin((alt), NativeMethodObject(getHeap(), _method_##name));
#define DEC_BUILTIN(name) \
	static void _method_##name(NativeMethodObject* method, machine::Machine& machine);
#define DEF_BUILTIN(clazz, name) \
	void clazz::_method_##name(NativeMethodObject* method, machine::Machine& machine)

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

class HookableObject : public Object
{
public:
	typedef Object* (*Getter)(HookableObject& self, ObjectHeap& heap);
	typedef void (*Setter)(HookableObject& self, ObjectHeap& heap, Object* const obj);
	explicit HookableObject(Object& parent);
	explicit HookableObject(HookableObject& parent, int hash);
	virtual ~HookableObject();
#define ADD_HOOK_ACCESSOR(name) \
		addGetter(#name, _getter_##name);\
		addSetter(#name, _setter_##name);
#define DEC_HOOK_ACCESSOR(name) \
	static Object* _getter_##name(HookableObject& self, ObjectHeap& heap); \
	static void _setter_##name(HookableObject& self, ObjectHeap& heap, Object* const obj);
#define DEF_HOOK_GETTER(clazz, name) \
	Object* clazz::_getter_##name(HookableObject& self, ObjectHeap& heap)
#define DEF_HOOK_SETTER(clazz, name) \
	void clazz::_setter_##name(HookableObject& self, ObjectHeap& heap, Object* const obj)

#define DEF_HOOK_ACCESSOR_STR(clazz, name, adapter) \
	Object* clazz::_getter_##name(HookableObject& self, ObjectHeap& heap)\
	{\
		return heap.newStringObject(dynamic_cast<clazz&>(self).adapter->name());\
	}\
	void clazz::_setter_##name(HookableObject& self, ObjectHeap& heap, Object* const obj)\
	{\
		dynamic_cast<clazz&>(self).adapter->name(obj->toStringObject()->toString());\
	}

#define DEF_HOOK_ACCESSOR_DOUBLE(clazz, name, adapter) \
	Object* clazz::_getter_##name(HookableObject& self, ObjectHeap& heap)\
	{\
		return heap.newNumericObject(dynamic_cast<clazz&>(self).adapter->name());\
	}\
	void clazz::_setter_##name(HookableObject& self, ObjectHeap& heap, Object* const obj)\
	{\
		dynamic_cast<clazz&>(self).adapter->name(obj->toNumericObject()->toNumeric());\
	}

#define DEF_HOOK_ACCESSOR_INT(clazz, name, adapter, type) \
	Object* clazz::_getter_##name(HookableObject& self, ObjectHeap& heap)\
	{\
		return heap.newNumericObject(dynamic_cast<clazz&>(self).adapter->name());\
	}\
	void clazz::_setter_##name(HookableObject& self, ObjectHeap& heap, Object* const obj)\
	{\
		dynamic_cast<clazz&>(self).adapter->name(static_cast<type>(obj->toNumericObject()->toNumeric()));\
	}
#define DEF_HOOK_ACCESSOR_BOOL(clazz, name, adapter) \
	Object* clazz::_getter_##name(HookableObject& self, ObjectHeap& heap)\
	{\
		return heap.newBooleanObject(dynamic_cast<clazz&>(self).adapter->name());\
	}\
	void clazz::_setter_##name(HookableObject& self, ObjectHeap& heap, Object* const obj)\
	{\
		dynamic_cast<clazz&>(self).adapter->name(obj->toBooleanObject()->toBool());\
	}

private:
	std::map<std::string, Getter> getterList;
	std::map<std::string, Setter> setterList;
protected:
	void addGetter(const std::string& name, Getter getter);
	void addSetter(const std::string& name, Setter setter);
public:
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
};

class SystemObject : public HookableObject
{
	system::System& system;
public:
	explicit SystemObject(Object& parent, system::System& system);
	virtual ~SystemObject();
public:
	DEC_HOOK_ACCESSOR(commentColor);
	DEC_HOOK_ACCESSOR(commentPlace);
	DEC_HOOK_ACCESSOR(commentSize);
	DEC_HOOK_ACCESSOR(commentInvisible);
	DEC_HOOK_ACCESSOR(commentReverse);
	DEC_HOOK_ACCESSOR(defaultSage);
	DEC_HOOK_ACCESSOR(postDisabled);
	DEC_HOOK_ACCESSOR(seekDisabled);
	DEC_HOOK_ACCESSOR(isLoaded);
	DEC_HOOK_ACCESSOR(isWide);
	DEC_HOOK_ACCESSOR(lastVideo);
public:
	DEC_BUILTIN(drawShape);
	DEC_BUILTIN(drawText);
	DEC_BUILTIN(commentTrigger);
	DEC_BUILTIN(timer);
	DEC_BUILTIN(jump);
	DEC_BUILTIN(jumpCancel);
	DEC_BUILTIN(seek);
	DEC_BUILTIN(addMarker);
	DEC_BUILTIN(getMarker);
	DEC_BUILTIN(sum);
	DEC_BUILTIN(showResult);
	DEC_BUILTIN(replace);
	DEC_BUILTIN(screenWidth);
	DEC_BUILTIN(screenHeight);
	DEC_BUILTIN(addButton);
	DEC_BUILTIN(playStartTime);
	DEC_BUILTIN(BGM);
	DEC_BUILTIN(playBGM);
	DEC_BUILTIN(stopBGM);
	DEC_BUILTIN(addAtPausePoint);
	DEC_BUILTIN(addPostRoute);
	DEC_BUILTIN(CM);
	DEC_BUILTIN(playCM);
};

class ShapeObject : public HookableObject
{
private:
	std::tr1::shared_ptr<system::Shape> shape;
public:
	explicit ShapeObject(Object& parent);
	explicit ShapeObject(ShapeObject& parent, int hash, std::tr1::shared_ptr<system::Shape> shape);
	virtual ~ShapeObject();
	std::tr1::shared_ptr<system::Shape> getShape(){return shape;};
public:
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(z);
	DEC_HOOK_ACCESSOR(shape);
	DEC_HOOK_ACCESSOR(width);
	DEC_HOOK_ACCESSOR(height);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(mask);
	DEC_HOOK_ACCESSOR(commentmask);
	DEC_HOOK_ACCESSOR(alpha);
	DEC_HOOK_ACCESSOR(rotation);
	DEC_HOOK_ACCESSOR(mover);

};

class SumObject : public HookableObject
{
private:
	std::tr1::shared_ptr<system::Sum> sum;
public:
	explicit SumObject(Object& parent);
	explicit SumObject(SumObject& parent, int hash, std::tr1::shared_ptr<system::Sum> sum);
	virtual ~SumObject();
	std::tr1::shared_ptr<system::Sum> getSum(){return sum;};
public:
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(size);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(enabled);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(asc);
	DEC_HOOK_ACCESSOR(unit);
	DEC_HOOK_ACCESSOR(buttononly);
	DEC_HOOK_ACCESSOR(words);
	DEC_HOOK_ACCESSOR(partial);
};
class SumResultObject : public HookableObject
{
private:
	std::tr1::shared_ptr<system::SumResult> sumResult;
public:
	explicit SumResultObject(Object& parent);
	explicit SumResultObject(SumResultObject& parent, int hash, std::tr1::shared_ptr<system::SumResult> sumResult);
	virtual ~SumResultObject();
	std::tr1::shared_ptr<system::SumResult> getSumResult(){return sumResult;};
public:
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(unit);
	DEC_HOOK_ACCESSOR(asc);
	DEC_HOOK_ACCESSOR(sum);
};
class ChatObject : public HookableObject
{
private:
	std::tr1::shared_ptr<system::Chat> chat;
public:
	explicit ChatObject(Object& parent);
	explicit ChatObject(ChatObject& parent, int hash, std::tr1::shared_ptr<system::Chat> chat);
	virtual ~ChatObject();
	std::tr1::shared_ptr<system::Chat> getChat(){return chat;};
public:
	DEC_HOOK_ACCESSOR(text);
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(z);
	DEC_HOOK_ACCESSOR(size);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(bold);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(filter);
	DEC_HOOK_ACCESSOR(alpha);
	DEC_HOOK_ACCESSOR(mover);
};

class ButtonObject : public HookableObject
{
private:
	std::tr1::shared_ptr<system::Button> button;
public:
	explicit ButtonObject(Object& parent);
	explicit ButtonObject(ButtonObject& parent, int hash, std::tr1::shared_ptr<system::Button> button);
	virtual ~ButtonObject();
	std::tr1::shared_ptr<system::Button> getButton(){return button;};
public:
	DEC_HOOK_ACCESSOR(message);
	DEC_HOOK_ACCESSOR(mail);
	DEC_HOOK_ACCESSOR(vpos);
	DEC_HOOK_ACCESSOR(commes);
	DEC_HOOK_ACCESSOR(commail);
	DEC_HOOK_ACCESSOR(comvisible);
	DEC_HOOK_ACCESSOR(limit);
	DEC_HOOK_ACCESSOR(hidden);
};

class ReplaceObject : public HookableObject
{
private:
	std::tr1::shared_ptr<system::Replace> replace;
public:
	explicit ReplaceObject(Object& parent);
	explicit ReplaceObject(ReplaceObject& parent, int hash, std::tr1::shared_ptr<system::Replace> replace);
	virtual ~ReplaceObject();
	std::tr1::shared_ptr<system::Replace> getReplace(){return replace;};
public:
	DEC_HOOK_ACCESSOR(src);
	DEC_HOOK_ACCESSOR(dst);
	DEC_HOOK_ACCESSOR(enabled);
	DEC_HOOK_ACCESSOR(target);
	DEC_HOOK_ACCESSOR(fill);
	DEC_HOOK_ACCESSOR(partial);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(size);
	DEC_HOOK_ACCESSOR(pos);
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
	explicit NativeMethodObject(ObjectHeap& heap, Method method);
	virtual ~NativeMethodObject();
	virtual void eval(machine::Machine& machine);
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

#undef DEC_BUILTIN
#undef DEC_HOOK_ACCESSOR

}
}
#endif /* MACHINE_OBJECT_H_ */
