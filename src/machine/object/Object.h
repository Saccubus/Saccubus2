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
protected:
	ObjectHeap& getHeap(){return heap;};
public:
	Object(ObjectHeap& heap, const unsigned int hash);
	virtual ~Object();
	unsigned int getHash(){return hash;};
public:
	int push(Object* const item);
	Object* setSlot(const std::string& name, Object* const item);
	Object* getSlot(const std::string& name);
	virtual bool isUndefined();
	virtual void eval(Machine& machine);
	virtual StringObject* toStringObject() = 0;
	virtual NumericObject* toNumericObject() = 0;
	virtual BooleanObject* toBooleanObject() = 0;
};

//-----------------------------------------------------------------------------

class LazyEvalObject : public Object
{

};
class LazyEvalNodeObject : public Object
{

};

class MethodObject : public Object
{

};

class NativeMethodObject : public MethodObject
{

};
class MethodNodeObject : public MethodObject
{

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

//-----------------------------------------------------------------------------

class ObjectHeap
{
private:
	std::vector<Object*> area1;
	std::vector<Object*> area2;
	std::vector<Object*> *from;
	std::vector<Object*> *to;
	unsigned int count;
private:
	BooleanObject trueObject;
	BooleanObject falseObject;
	UndefinedObject undefinedObject;
public:
	ObjectHeap();
	~ObjectHeap();
	Object* newObject();
	Object* newObject(const Object* parent);
public:
	LazyEvalObject* newLazyEvalObject(const tree::ObjectNode* objNode);
	LazyEvalNodeObject* newLazyEvalNodeObject(tree::Node* node);
public:
	Object* newArray(Object* obj, ...);
public:
	StringObject* newStringObject(const std::string& str);
	BooleanObject* newBooleanObject(const bool val);
	NumericObject* newNumericObject(const double num);
	UndefinedObject* newUndefinedObject();
public:
	void gc(const Object* global);
};

} /* namespace machine */
#endif /* MACHINE_OBJECT_H_ */
