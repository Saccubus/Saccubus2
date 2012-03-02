/*
 * Heap.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "Cast.h"
#include "Heap.h"
#include "../logging/Logging.h"
#include <cstdarg>
#include <cmath>
#include <set>
#include <algorithm>
#include <tr1/functional>
#include <memory>

namespace nekomata{
namespace object{

const static std::string TAG("HEAP");

ObjectHeap::ObjectHeap(logging::Logger& log, system::System& system, RootHolder& rootHolder)
:log(log)
,rootHolder(rootHolder)
,from(&area1)
,to(&area2)
,count(0)
,gcThreshold(10000)
,gcCount(0)
,rawObject(*this, true)
,baseObject(*this, false)
,systemObject(baseObject, system)
,baseChatObject(baseObject)
,baseReplaceObject(baseObject)
,baseSumObject(baseObject)
,baseSumResultObject(baseObject)
,baseButtonObject(baseObject)
,baseShapePbject(baseObject)
,baseLambdaObject(*this)
,baseLambdaScopeObject(*this)
,baseStringObject(baseObject)
,baseNumericObject(baseObject)
,trueObject(baseObject, true)
,falseObject(baseObject, false)
,undefinedObject(*this)
{
}
ObjectHeap::~ObjectHeap()
{
	for(std::vector<Object*>::iterator it = from->begin();it!=from->begin();++it)
	{
		Object* const obj = *it;
		if(obj->getNativeRef() > 0){
			int nativeRef = obj->getNativeRef();
			log.e(TAG, 0, "[FIXME] Memory leaked! %s has %d native refs on exit.", cast<std::string>(Handler<Object>(obj)).c_str(), nativeRef);
		}
		delete *it;
	}
}

Handler<SystemObject> ObjectHeap::getSystemObject()
{
	return Handler<SystemObject>(&systemObject);
}

Handler<ChatObject> ObjectHeap::newChatObject(std::tr1::shared_ptr<system::Chat> chat)
{
	const Handler<ChatObject> obj(new ChatObject(baseChatObject, createHash(), chat));
	registObject(obj.get());
	return obj;
}
Handler<ReplaceObject> ObjectHeap::newReplaceObject(std::tr1::shared_ptr<system::Replace> replace)
{
	const Handler<ReplaceObject> obj(new ReplaceObject(baseReplaceObject, createHash(), replace));
	registObject(obj.get());
	return obj;
}
Handler<SumObject> ObjectHeap::newSumObject(std::tr1::shared_ptr<system::Sum> sum)
{
	const Handler<SumObject> obj(new SumObject(baseSumObject, createHash(), sum));
	registObject(obj.get());
	return obj;
}
Handler<SumResultObject> ObjectHeap::newSumResultObject(std::tr1::shared_ptr<system::SumResult> sumResult)
{
	const Handler<SumResultObject> obj(new SumResultObject(baseSumResultObject, createHash(), sumResult));
	registObject(obj.get());
	return obj;
}
Handler<ButtonObject> ObjectHeap::newButtonObject(std::tr1::shared_ptr<system::Button> button)
{
	const Handler<ButtonObject> obj(new ButtonObject(baseButtonObject, createHash(), button));
	registObject(obj.get());
	return obj;
}
Handler<ShapeObject> ObjectHeap::newShapeObject(std::tr1::shared_ptr<system::Shape> shape)
{
	const Handler<ShapeObject> obj(new ShapeObject(baseShapePbject, createHash(), shape));
	registObject(obj.get());
	return obj;
}

Handler<Object> ObjectHeap::newObject()
{
	Handler<Object> obj(new Object(baseObject, createHash()));
	registObject(obj.get());
	return obj;
}

Handler<Object> ObjectHeap::newRawObject()
{
	Handler<Object> obj(new Object(rawObject, createHash()));
	registObject(obj.get());
	return obj;
}

Handler<Object> ObjectHeap::newArrayObject(const size_t argc, ...)
{
	Handler<Object> obj(new Object(rawObject, createHash()));

	va_list list;
	va_start(list, argc);
	for(size_t i=0;i<argc;++i){
		obj->push(Handler<Object>(va_arg(list, Object*)));
	}
	va_end(list);

	registObject(obj.get());
	return obj;
}

Handler<LambdaScopeObject> ObjectHeap::newLambdaScopeObject(const Handler<Object> arg)
{
	Handler<LambdaScopeObject> obj(new LambdaScopeObject(baseLambdaScopeObject, createHash(), arg));
	registObject(obj.get());
	return obj;
}

void ObjectHeap::registObject(Object* obj){
	if(gcThreshold <= this->from->size()){
		this->gc();
	}
	this->from->push_back(obj);
}

Handler<StringObject> ObjectHeap::newStringObject(const std::string & str)
{
	Handler<StringObject> obj(new StringObject(baseStringObject, createHash(), str));
	registObject(obj.get());
	return obj;
}



Handler<BooleanObject> ObjectHeap::newBooleanObject(const bool val)
{
	if(val){
		return Handler<BooleanObject>(&trueObject);
	}else{
		return Handler<BooleanObject>(&falseObject);
	}
}



Handler<NumericObject> ObjectHeap::newNumericObject(const double num)
{
	Handler<NumericObject> obj(new NumericObject(baseNumericObject, createHash(), num));
	registObject(obj.get());
	return obj;
}

Handler<UndefinedObject> ObjectHeap::newUndefinedObject()
{
	return Handler<UndefinedObject>(&undefinedObject);
}

Handler<LazyEvalObject> ObjectHeap::newLazyEvalObject(machine::Machine& machine, const tree::ObjectNode *objNode)
{
	Handler<LazyEvalObject> obj(new LazyEvalObject(baseObject, createHash(), machine, objNode));
	registObject(obj.get());
	return obj;
}

Handler<MethodNodeObject> ObjectHeap::newMethodNodeObject(const Handler<Object> scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule, std::vector<std::string>& argList)
{
	Handler<MethodNodeObject> obj(new MethodNodeObject(rawObject, createHash(), scope, node, rule, argList));
	registObject(obj.get());
	return obj;
}
Handler<MethodNodeObject> ObjectHeap::newMethodNodeObject(const Handler<Object> scope, const tree::Node* node, MethodNodeObject::LocalScopeRule rule)
{
	Handler<MethodNodeObject> obj(new MethodNodeObject(rawObject, createHash(), scope, node, rule));
	registObject(obj.get());
	return obj;
}

Handler<LambdaObject> ObjectHeap::newLambdaObject(const Handler<Object> scope, const tree::Node* node)
{
	const Handler<LambdaObject> obj(new LambdaObject(baseLambdaObject, createHash(), scope, node));
	registObject(obj.get());
	return obj;
}

bool deleteFunc(int color, std::set<Object*, std::tr1::function<bool(Object*, Object*)> >* unused, Object* obj)
{
	if(obj->getColor() == color){
		return false;
	}else{
		unused->insert(obj);
		return true;
	}
}

void ObjectHeap::gc()
{
	gcCount++;
	size_t before = this->from->size();

	{
		std::auto_ptr<RootHolder::Iterator> it(rootHolder.newIterator());
		while(it->hasNext())
		{
			Object* const obj = it->next();
			obj->mark(this->gcCount);
		}
	}
	std::set<Object*> unused;
	for(std::vector<Object*>::const_iterator it=from->begin();it!=from->end();++it)
	{
		if((*it)->getColor() != gcCount && (*it)->getNativeRef() <= 0){
			unused.insert(*it);
		}else{
			to->push_back(*it);
		}
	}

	log.d(TAG, 0, "Garbage collected: %d -> %d objects (%d%% collected)", before, before-unused.size(), unused.size()*100/before);
	for(std::set<Object*>::const_iterator it=unused.begin();it!=unused.end();++it)
	{
		delete (*it);
	}

	this->from->clear();
	std::swap(from, to);
}

int ObjectHeap::createHash()
{
	return ++count;
}

}
}
