/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cinamo/Handler.h>
#include <nekomata/classdefs.h>
#include "Object.h"
#include "SystemObject.h"

namespace nekomata{
namespace object{

using cinamo::Handler;

class RootHolder{
public:
	class Iterator
	{
	public:
		Iterator(){};
		virtual ~Iterator(){};
		virtual bool hasNext() = 0;
		virtual Object* next() = 0;
	};
public:
	RootHolder(){};
	virtual ~RootHolder(){};
	virtual Iterator* newIterator() = 0;
};

class ObjectHeap
{
public:
	logging::Logger& log;
private:
	explicit ObjectHeap();
	explicit ObjectHeap(const ObjectHeap& other);
private:
	RootHolder& rootHolder;
	std::vector<Object*> area1;
	std::vector<Object*> area2;
	std::vector<Object*> *from;
	std::vector<Object*> *to;
	int count;
	size_t gcThreshold;
	int gcCount;
private:
	/* これらの関数はGCで管理しない */
	Object rawObject;
	Object baseObject;
//
	SystemObject systemObject;
	LabelObject baseLabelObject;
	ReplaceObject baseReplaceObject;
	SumObject baseSumObject;
	SumResultObject baseSumResultObject;
	ShapeObject baseShapePbject;
//
	LazyEvalObject baseLazyEvalObject;
	LambdaObject baseLambdaObject;
	LambdaScopeObject baseLambdaScopeObject;
	StringObject baseStringObject;
	NumericObject baseNumericObject;
	BooleanObject trueObject;
	BooleanObject falseObject;
	UndefinedObject undefinedObject;
	/*GCで管理するオブジェクトを登録*/
	int createHash();
	void registerObject(Object* obj);
public:
	explicit ObjectHeap(logging::Logger& log, system::System& system, RootHolder& rootHolder);
	~ObjectHeap();
public:
	Handler<SystemObject> getSystemObject();
	Handler<LabelObject> newLabelObject(Handler<system::Label> label);
	Handler<ReplaceObject> newReplaceObject(Handler<system::Replace> replace);
	Handler<SumObject> newSumObject(Handler<system::Sum> sum);
	Handler<SumResultObject> newSumResultObject(Handler<system::SumResult> sumResult);
	Handler<ShapeObject> newShapeObject(Handler<system::Shape> shape);
public:
	Handler<Object> newRawObject();
	Handler<LambdaScopeObject> newLambdaScopeObject(const Handler<Object> arg);
	Handler<Object> newObject();
	Handler<Object> newArrayObject(const size_t argc, ...);
public:
	Handler<LazyEvalObject> newLazyEvalObject(machine::Machine& machine, const tree::ObjectNode* objNode);
	Handler<MethodNodeObject> newMethodNodeObject(const Handler<Object> scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule, std::vector<std::string>& argList);
	Handler<MethodNodeObject> newMethodNodeObject(const Handler<Object> scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule);
	Handler<LambdaObject> newLambdaObject(const Handler<Object> scope, const tree::Node* node);
public:
	Handler<StringObject> newStringObject(std::string const& str);
	Handler<BooleanObject> newBooleanObject(const bool val);
	Handler<NumericObject> newNumericObject(const double num);
	Handler<UndefinedObject> newUndefinedObject();
public:
	void gc();
};

}}
