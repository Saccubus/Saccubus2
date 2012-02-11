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
	ObjectHeap* const parentHeap;
	std::vector<Object*> objectList;
	std::map<std::string, Object*> objectMap;
public:
	Object(ObjectHeap* const heap);
	virtual ~Object();
public:
	//virtual Object* eval(Machine& machine);
	virtual StringObject* toStringObject() = 0;
	virtual NumericObject* toNumericObject() = 0;
	virtual BooleanObject* toBooleanObject() = 0;
};

class NodeObject : public Object
{

};
class LiteralObject : public Object
{

};
class StringObject : public LiteralObject
{

};
class BooleanObject : public LiteralObject
{

};
class IntegerObject : public LiteralObject
{

};

class UndefinedObject : public Object
{

};

//-----------------------------------------------------------------------------

class ObjectHeap
{
private:
	std::vector<Object*> area1;
	std::vector<Object*> area2;
	std::vector<Object*> *from;
	std::vector<Object*> *to;
public:
	Object* newObject(const Object* parent);
	Object* newObject(const tree::ObjectNode* objNode);
	StringObject* newStringObject(const std::string& str);
	BooleanObject* newBooleanObject(const bool val);
	NumericObject* newNumericObject(const double num);
	NodeObject* newNodeObject(tree::Node* node);
	void gc(const Object* global);
};

} /* namespace machine */
#endif /* OBJECT_H_ */
