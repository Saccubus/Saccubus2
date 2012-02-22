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
#include "../../classdefs.h"

namespace nekomata{
namespace machine{

class ObjectHeap
{
public:
	class GarbageCollectionCallback{
	public:
		GarbageCollectionCallback(){};
		virtual ~GarbageCollectionCallback(){};
		virtual void needGC(ObjectHeap& self) = 0;
	};
private:
	GarbageCollectionCallback& callback;
	logging::Logger& log;
	std::vector<Object*> area1;
	std::vector<Object*> area2;
	std::vector<Object*> *from;
	std::vector<Object*> *to;
	int count;
	size_t lastObjectSize;
	int gcCount;
private:
	void injectMethods(Object* const obj, std::map<std::string, NativeMethodObject>& methods);
	void setWorld();
	/* これらの関数はGCで管理しない */
	BooleanObject trueObject;
	BooleanObject falseObject;
	UndefinedObject undefinedObject;
	std::map<std::string, NativeMethodObject> rawObjectBuiltinMethod;
	std::map<std::string, NativeMethodObject> baseObjectBuiltinMethod;
	std::map<std::string, NativeMethodObject> baseLambdaObjectBuiltinMethod;
	std::map<std::string, NativeMethodObject> baseLambdaScopeObjectBuiltinMethod;
	std::map<std::string, NativeMethodObject> baseStringObjectBuiltinMethod;
	std::map<std::string, NativeMethodObject> baseNumericObjectBuiltinMethod;
	std::map<std::string, NativeMethodObject> baseBooleanObjectBuiltinMethod;


	/*GCで管理するオブジェクトを登録*/
	int createHash();
	void registObject(Object* obj);
public:
	explicit ObjectHeap(logging::Logger& log, GarbageCollectionCallback& callback);
	~ObjectHeap();
public:
	Object* newRawObject();
	LambdaScopeObject* newLambdaScopeObject(Object* const arg);
	Object* newObject();
public:
	LazyEvalObject* newLazyEvalObject(Machine& machine, const tree::ObjectNode* objNode);
	MethodNodeObject* newMethodNodeObject(Object* const scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule, std::vector<std::string>& argList);
	MethodNodeObject* newMethodNodeObject(Object* const scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule);
	LambdaObject* newLambdaObject(Object* const scope, const tree::Node* node);
public:
	Object* newArray(Object* obj, ...);
public:
	StringObject* newStringObject(const std::string& str);
	BooleanObject* newBooleanObject(const bool val);
	NumericObject* newNumericObject(const double num);
	UndefinedObject* newUndefinedObject();
public:
	void checkGC();
	void gc(std::vector<Object*>& root);
};
}
}

#endif /* MACHINE_HEAP_H_ */
