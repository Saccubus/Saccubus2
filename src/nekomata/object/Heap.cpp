/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdarg>
#include <cmath>
#include <set>
#include <algorithm>
#include <tr1/functional>
#include <memory>
#include <nekomata/logging/Logging.h>

#include "Object.h"
#include "SystemObject.h"
#include "Cast.h"
#include "Heap.h"

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
,baseLabelObject(baseObject)
,baseReplaceObject(baseObject)
,baseSumObject(baseObject)
,baseSumResultObject(baseObject)
,baseShapePbject(baseObject)
,baseLazyEvalObject(baseObject)
,baseLambdaObject(*this)
,baseLambdaScopeObject(rawObject)
,baseStringObject(baseObject)
,baseNumericObject(baseObject)
,trueObject(baseObject, true)
,falseObject(baseObject, false)
,undefinedObject(rawObject)
{
	systemObject.setSlot("Object", newObject());
	systemObject.setSlot("undefined", newUndefinedObject());
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

Handler<LabelObject> ObjectHeap::newLabelObject(Handler<system::Label> label)
{
	const Handler<LabelObject> obj(new LabelObject(baseLabelObject, createHash(), label));
	registObject(obj.get());
	return obj;
}
Handler<ReplaceObject> ObjectHeap::newReplaceObject(Handler<system::Replace> replace)
{
	const Handler<ReplaceObject> obj(new ReplaceObject(baseReplaceObject, createHash(), replace));
	registObject(obj.get());
	return obj;
}
Handler<SumObject> ObjectHeap::newSumObject(Handler<system::Sum> sum)
{
	const Handler<SumObject> obj(new SumObject(baseSumObject, createHash(), sum));
	registObject(obj.get());
	return obj;
}
Handler<SumResultObject> ObjectHeap::newSumResultObject(Handler<system::SumResult> sumResult)
{
	const Handler<SumResultObject> obj(new SumResultObject(baseSumResultObject, createHash(), sumResult));
	registObject(obj.get());
	return obj;
}
Handler<ShapeObject> ObjectHeap::newShapeObject(Handler<system::Shape> shape)
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
	Handler<LazyEvalObject> obj(new LazyEvalObject(baseLazyEvalObject, createHash(), machine, objNode));
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
	//ネイティブから参照されてるオブジェクトもルート扱い。
	for(std::vector<Object*>::const_iterator it=from->begin();it!=from->end();++it)
	{
		if((*it)->getNativeRef() > 0){
			(*it)->mark(gcCount);
		}
	}
	std::set<Object*> unused;
	for(std::vector<Object*>::const_iterator it=from->begin();it!=from->end();++it)
	{
		if((*it)->getColor() != gcCount){
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

}}
