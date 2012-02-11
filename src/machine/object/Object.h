/*
 * Object.h
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include "../../tree/Node.h"

namespace machine
{

class ObjectHeap;
class LiteralObject;
class StringObject;
class BooleanObject;
class NumericObject;
class NodeObject;
class UndefinedObject;

class Object
{
private:
	ObjectHeap* const heap;
	const int hash;
	std::vector<Object*> objectList;
	std::map<std::string, Object*> objectMap;
protected:
	ObjectHeap& getHeap(){return *heap;};
public:
	Object(ObjectHeap* const heap, const unsigned int hash);
	virtual ~Object();
	unsigned int getHash(){return hash;};
public:
	virtual void send(std::string& message, Object* with){};
	virtual StringObject* toStringObject() = 0;
	virtual NumericObject* toNumericObject() = 0;
	virtual BooleanObject* toBooleanObject() = 0;
};

class NodeObject : public Object
{

};
class LiteralObject : public Object
{
protected:
	LiteralObject(ObjectHeap* const heap, const unsigned int hash):Object(heap,hash){};
	~LiteralObject(){};
};
class StringObject : public LiteralObject
{
private:
	const std::string value;
public:
	StringObject(ObjectHeap* const heap, const unsigned int hash, const std::string& value);
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
	BooleanObject(ObjectHeap* const heap, const unsigned int hash, const bool value);
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
	NumericObject(ObjectHeap* const heap, const unsigned int hash, const double value);
	~NumericObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	double toNumeric();
};

class UndefinedObject : public Object
{
public:
	UndefinedObject(ObjectHeap* const heap, const unsigned int hash);
	~UndefinedObject();
public:
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
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
	Object* newObject(const Object* parent);
	Object* newObject(const tree::ObjectNode* objNode);
	StringObject* newStringObject(const std::string& str);
	BooleanObject* newBooleanObject(const bool val);
	NumericObject* newNumericObject(const double num);
	NodeObject* newNodeObject(tree::Node* node);
	UndefinedObject* newUndefinedObject();
	void gc(const Object* global);
};

} /* namespace machine */
#endif /* OBJECT_H_ */
