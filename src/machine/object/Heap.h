/*
 * Heap.h
 *
 *  Created on: 2012/02/15
 *      Author: psi
 */

#ifndef MACHINE_HEAP_H_
#define MACHINE_HEAP_H_
#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include "../classdef.h"
#include "Object.h"

namespace machine
{
class ObjectHeap
{
private:
	std::vector<Object*> area1;
	std::vector<Object*> area2;
	std::vector<Object*> *from;
	std::vector<Object*> *to;
	unsigned int count;
private:
	/* これらの関数はGCで管理しない */
	void injectMethods(Object& obj, std::map<std::string, NativeMethodObject>& methods);
	void setWorld();

	Object topLevelObject;
	std::map<std::string, NativeMethodObject> topLebelObjectBuiltinMethod;

	Object baseObject;
	std::map<std::string, NativeMethodObject> baseObjectBuiltinMethod;

	StringObject baseStringObject;
	std::map<std::string, NativeMethodObject> baseStringObjectBuiltinMethod;

	NumericObject baseNumericObject;
	std::map<std::string, NativeMethodObject> baseNumericObjectBuiltinMethod;

	BooleanObject trueObject;
	BooleanObject falseObject;
	std::map<std::string, NativeMethodObject> baseBooleanObjectBuiltinMethod;

	UndefinedObject undefinedObject;

	/*GCで管理するオブジェクトを登録*/
	unsigned int createHash();
	void registObject(Object* obj);
public:
	ObjectHeap();
	~ObjectHeap();
	Object* newObject();
public:
	LazyEvalObject* newLazyEvalObject(const tree::ObjectNode* objNode);
	LazyEvalNodeObject* newLazyEvalNodeObject(const tree::Node* node);
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
}


#endif /* MACHINE_HEAP_H_ */
