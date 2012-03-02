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
#include "../classdefs.h"
#include "Object.h"

namespace nekomata{
namespace object{

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
	ChatObject baseChatObject;
	ReplaceObject baseReplaceObject;
	SumObject baseSumObject;
	SumResultObject baseSumResultObject;
	ButtonObject baseButtonObject;
	ShapeObject baseShapePbject;
//
	LambdaObject baseLambdaObject;
	LambdaScopeObject baseLambdaScopeObject;
	StringObject baseStringObject;
	NumericObject baseNumericObject;
	BooleanObject trueObject;
	BooleanObject falseObject;
	UndefinedObject undefinedObject;
	/*GCで管理するオブジェクトを登録*/
	int createHash();
	void registObject(Object* obj);
public:
	explicit ObjectHeap(logging::Logger& log, system::System& system, RootHolder& rootHolder);
	~ObjectHeap();
public:
	Handler<SystemObject> getSystemObject();
	Handler<ChatObject> newChatObject(std::tr1::shared_ptr<system::Chat> chat);
	Handler<ReplaceObject> newReplaceObject(std::tr1::shared_ptr<system::Replace> replace);
	Handler<SumObject> newSumObject(std::tr1::shared_ptr<system::Sum> sum);
	Handler<SumResultObject> newSumResultObject(std::tr1::shared_ptr<system::SumResult> sumResult);
	Handler<ButtonObject> newButtonObject(std::tr1::shared_ptr<system::Button> button);
	Handler<ShapeObject> newShapeObject(std::tr1::shared_ptr<system::Shape> shape);
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
	Handler<StringObject> newStringObject(const std::string& str);
	Handler<BooleanObject> newBooleanObject(const bool val);
	Handler<NumericObject> newNumericObject(const double num);
	Handler<UndefinedObject> newUndefinedObject();
public:
	void gc();
};
}
}

#endif /* MACHINE_HEAP_H_ */
