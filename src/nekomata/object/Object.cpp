/*
 * Object.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include <cmath>
#include <sstream>
#include <algorithm>
#include <tr1/functional>
#include "Object.h"
#include "Cast.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"

namespace nekomata{
namespace object
{

static std::string TAG(__FILE__);

Object::Object(ObjectHeap& heap)
:heap(heap), hash(-1), color(0), nativeRef(0), builtins(0), _frozen(false)
{
}
Object::Object(ObjectHeap& heap, bool isRaw)
:heap(heap), hash(-1), color(0), nativeRef(0), builtins(0), _frozen(false)
{
	ADD_BUILTIN(setSlot);
	ADD_BUILTIN(getSlot);
	ADD_BUILTIN(clone);
	if(!isRaw){
		ADD_BUILTIN(def);
		ADD_BUILTIN(def_kari);

		ADD_BUILTIN(index);
		ADD_BUILTIN(indexSet);
		ADD_BUILTIN(size);
		ADD_BUILTIN(unshift);
		ADD_BUILTIN(push);
		ADD_BUILTIN(shift);
		ADD_BUILTIN(pop);
		ADD_BUILTIN(sort);
		ADD_BUILTIN(sum);
		ADD_BUILTIN(product);
		ADD_BUILTIN(join);

		ADD_BUILTIN(if);
		ADD_BUILTIN(while_kari);
		ADD_BUILTIN(lambda);

		ADD_BUILTIN(distance);
		ADD_BUILTIN(rand);
	}
	includeBuitin();
}
Object::Object(Object& parent, const unsigned int hash)
:heap(parent.getHeap()), hash(hash), color(0), nativeRef(0), builtins(0)
{
	objectList.insert(objectList.end(), parent.objectList.begin(), parent.objectList.end());
	objectMap.insert(parent.objectMap.begin(), parent.objectMap.end());
}


Object::~Object()
{
	if(builtins){
		delete builtins;
	}
}
void Object::addBuiltin(const std::string& name, NativeMethodObject obj)
{
	if(!builtins){
		builtins = new BuiltinMethods();
	}
	builtins->insert(BuiltinMethodPair(name, obj));
}
void Object::includeBuitin()
{
	if(!builtins){
		return;
	}
	for(BuiltinMethods::iterator it = builtins->begin(); it!=builtins->end();++it){
		Object::setSlot(it->first, Handler<Object>(&it->second));
	}
}

void Object::eval(machine::Machine& machine){
	machine.pushResult(Handler<Object>(this));
}

void Object::mark(int color)
{
	if(this->color == color){
		return;
	}
	this->color = color;
	for(std::vector<Object*>::const_iterator it=objectList.begin();it!=objectList.end();++it){
		(*it)->mark(color);
	}
	for(std::map<std::string, Object*>::const_iterator it=objectMap.begin();it!=objectMap.end();++it){
		it->second->mark(color);
	}
}



logging::Logger& Object::log()
{
	return heap.log;
}

int Object::getColor(){
	return this->color;
}
int Object::getNativeRef(){
	return this->nativeRef;
}

int Object::incNativeRef()
{
	++nativeRef;
	return nativeRef;
}
int Object::decNativeRef()
{
	--nativeRef;
	if(nativeRef < 0){
		log().e(TAG, 0, "[BUG] Native ref = %d < 0 on %s", nativeRef, cast<std::string>(Handler<Object>(this)).c_str());
	}
	return nativeRef;
}

bool Object::frozen()
{
	return _frozen;
}
void Object::freeze()
{
	_frozen |= true;
}


Handler<Object> Object::unshift(const Handler<Object> item)
{
	if(frozen()){
		log().w(TAG, 0, "\"unshift\" called, but obj %s is frozen.", toString().c_str());
	}else{
		objectList.insert(objectList.begin(), item.get());
	}
	return Handler<Object>(this);
}
Handler<Object> Object::push(const Handler<Object> item)
{
	if(frozen()){
		log().w(TAG, 0, "\"push\" called, but obj %s is frozen.", toString().c_str());
	}else{
		objectList.push_back(item.get());
	}
	return Handler<Object>(this);
}
Handler<Object> Object::shift()
{
	if(frozen()){
		log().w(TAG, 0, "\"shift\" called, but obj %s is frozen.", toString().c_str());
		return heap.newUndefinedObject();
	}else{
		if(Object::size() > 0){
			const Handler<Object> obj(objectList.front());
			objectList.erase(objectList.begin());
			return obj;
		}else{
			return heap.newUndefinedObject();
		}
	}
}
Handler<Object> Object::pop()
{
	if(frozen()){
		log().w(TAG, 0, "\"pop\" called, but obj %s is frozen.", toString().c_str());
		return heap.newUndefinedObject();
	} else {
		if(Object::size() > 0){
			const Handler<Object> obj(objectList.back());
			objectList.pop_back();
			return obj;
		}else{
			return heap.newUndefinedObject();
		}
	}
}
Handler<Object> Object::index(size_t idx)
{
	if(frozen()){
		log().w(TAG, 0, "\"index\" called, but obj %s is frozen.", toString().c_str());
		return heap.newUndefinedObject();
	} else {
		if(Object::has(idx)){
			return Handler<Object>(objectList.at(idx));
		}else{
			return heap.newUndefinedObject();
		}
	}
}
Handler<Object> Object::indexSet(size_t idx, Handler<Object> item)
{
	if(frozen()){
		log().w(TAG, 0, "\"indexSet\" called, but obj %s is frozen.", toString().c_str());
	} else {
		if(idx < objectList.size()){
			objectList[idx] = item.get();
		}else{
			objectList.insert(objectList.end(), idx-objectList.size(), getHeap().newUndefinedObject().get());
			objectList.push_back(item.get());
		}
	}
	return item;
}

size_t Object::size()
{
	return objectList.size();
}
bool Object::has(size_t idx)
{
	return idx >= 0 && idx < Object::size();
}

bool Object::has(const std::string& key)
{
	return objectMap.count(key) > 0;
}
std::vector<std::string> Object::getSlotNames()
{
	std::vector<std::string> slotList;
	for(SlotMapIterator it = objectMap.begin(); it != objectMap.end(); ++it){
		slotList.push_back(it->first);
	}
	return slotList;
}

bool Object::isUndefined(){
	return false;
}
Handler<Object> Object::setSlot(const std::string& name, const Handler<Object> item)
{
	if(frozen()){
		log().w(TAG, 0, "\"setSlot\" called, but obj %s is frozen.", toString().c_str());
	} else {
		objectMap.erase(name);
		objectMap.insert(SlotMapPair(name, item.get()));
	}
	return Handler<Object>(this);
}
Handler<Object> Object::getSlot(const std::string& name){
	SlotMapIterator it = objectMap.find(name);
	if(it == objectMap.end()){
		return getHeap().newUndefinedObject();
	}else{
		return Handler<Object>(it->second);
	}
}

size_t Object::slotSize()
{
	return objectMap.size();
}


std::string Object::toString()
{
	std::stringstream ss;
	ss << "<< Object: " << getHash() << ">>";
	return ss.str();
}
double Object::toNumeric()
{
	return NAN;
}
bool Object::toBool()
{
	return true;
}


//---------------------------------------------------------------------------------------------------------------------
// メソッド
//---------------------------------------------------------------------------------------------------------------------

DEF_BUILTIN(Object, def)
{
	const Handler<Object> self(machine.getSelf());
	const Handler<LazyEvalObject> arg(machine.getArgument());
	if(!arg || arg->size() < 2){
		machine.log.w(TAG, 0, "Invalid method define call.");
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	const tree::InvokeNode* const invokeNode = dynamic_cast<const tree::InvokeNode*>(arg->getRawNode()->index(0));
	const tree::BindNode* const bindNode = dynamic_cast<const tree::BindNode*>(arg->getRawNode()->index(0));
	if(invokeNode){
		const Handler<MethodNodeObject> _method = self->getHeap().newMethodNodeObject(machine.getLocal(), arg->getRawNode()->index(1), MethodNodeObject::def);
		self->setSlot(invokeNode->getMessageName(), _method);
		machine.pushResult(_method);
	}else if(bindNode){
		const tree::InvokeNode* const nameNode = dynamic_cast<const tree::InvokeNode*>(bindNode->getExprNode());
		if(!nameNode){
			machine.log.w(TAG, &bindNode->location(), "Invalid method define. Method was defined without name.");
			machine.pushResult(self->getHeap().newUndefinedObject());
			return;
		}
		const tree::ObjectNode* const argNode =  bindNode->getObjectNode();
		std::vector<std::string> argList;
		const size_t argc =argNode->size();
		for(size_t i=0;i<argc;++i){
			const tree::InvokeNode* const argNameNode = dynamic_cast<const tree::InvokeNode*>(argNode->index(i));
			if(!argNameNode){
				machine.log.w(TAG, &argNode->location(), "Invalid argument. Argument was defined without name.");
				continue;
			}
			argList.push_back(argNameNode->getMessageName());
		}
		const Handler<MethodNodeObject> _method = self->getHeap().newMethodNodeObject(machine.getLocal(), arg->getRawNode()->index(1), MethodNodeObject::def, argList);
		self->setSlot(nameNode->getMessageName(), _method);
		machine.pushResult(_method);
	}else{
		machine.log.w(TAG, 0, "Invalid method define. There is no name for the method.");
		machine.pushResult(self->getHeap().newUndefinedObject());
	}
}
DEF_BUILTIN(Object, def_kari)
{
	const Handler<Object> self(machine.getSelf());
	const Handler<LazyEvalObject> arg(machine.getArgument());
	if(!arg || arg->size() < 2){
		machine.log.w(TAG, 0, "Invalid def_kari call. There is neither name nor method body.");
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	std::string methodName = cast<std::string>(arg->index(0));
	const Handler<MethodNodeObject>_method(self->getHeap().newMethodNodeObject(machine.getLocal(), arg->getRawNode()->index(1), MethodNodeObject::def_kari));
	self->setSlot(methodName, _method);
	machine.pushResult(_method);
}

DEF_BUILTIN(Object, index)
{
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->index(cast<size_t>(machine.getArgument()->index(0))));
}
DEF_BUILTIN(Object, indexSet)
{
	const Handler<Object> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	size_t const idx = cast<size_t>(arg->index(0));
	machine.pushResult(self->indexSet(idx, arg->index(1)));
}
DEF_BUILTIN(Object, size)
{
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->getHeap().newNumericObject(self->size()));
}
DEF_BUILTIN(Object, unshift)
{
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->unshift(machine.getArgument()->index(0)));
}
DEF_BUILTIN(Object, push)
{
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->push(machine.getArgument()->index(0)));
}
DEF_BUILTIN(Object, shift)
{
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->shift());
}
DEF_BUILTIN(Object, pop)
{
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->pop());
}

bool Object::_sort_func(machine::Machine& machine, Object* const self, Object* const other)
{
	return cast<bool>(machine.send(Handler<Object>(self), "lessThan", self->getHeap().newArrayObject(1, other)));
}

DEF_BUILTIN(Object, sort)
{
	const Handler<Object> self(machine.getSelf());
	std::sort(self->objectList.begin(), self->objectList.end(),std::tr1::bind(&Object::_sort_func, machine, std::tr1::placeholders::_1, std::tr1::placeholders::_2));
	machine.pushResult(self);
}
DEF_BUILTIN(Object, sum)
{
	const Handler<Object> self(machine.getSelf());
	double result = 0.0;
	const size_t max = self->size();
	for(size_t i=0;i<max;++i){
		result += cast<double>(self->index(i));
	}
	machine.pushResult(self->getHeap().newNumericObject(result));
}
DEF_BUILTIN(Object, product)
{
	const Handler<Object> self(machine.getSelf());
	double result = 1.0;
	const size_t max = self->size();
	for(size_t i=0;i<max;++i){
		result *= cast<double>(self->index(i));
	}
	machine.pushResult(self->getHeap().newNumericObject(result));
}
DEF_BUILTIN(Object, join)
{
	const Handler<Object> self(machine.getSelf());
	std::stringstream ss;
	const Handler<Object> arg(machine.getArgument());
	const size_t max = self->size();
	if(max <= 0){
		machine.pushResult(self->getHeap().newStringObject(""));
		return;
	}
	std::string sep = cast<std::string>(arg->index(0));
	ss << cast<std::string>(self->index(0));
	for(size_t i=1;i<max;++i){
		ss << sep << cast<std::string>(arg->index(i));
	}
	machine.pushResult(self->getHeap().newStringObject(ss.str()));
}


DEF_BUILTIN(Object, setSlot)
{
	const Handler<Object> arg(machine.getArgument());
	const Handler<Object> self(machine.getSelf());
	std::string name = cast<std::string>(arg->index(0));
	const Handler<Object> obj(arg->index(1));
	machine.pushResult(self->setSlot(name, obj));
}
DEF_BUILTIN(Object, getSlot)
{
	const Handler<Object> self(machine.getSelf());
	std::string name = cast<std::string>(machine.getArgument()->index(0));
	const Handler<Object> obj(self->getSlot(name));
	machine.pushResult(obj);
}
DEF_BUILTIN(Object, clone){
	//FIXME
	const Handler<Object> self(machine.getSelf());
	machine.pushResult(self->getHeap().newUndefinedObject());
}

DEF_BUILTIN(Object, if)
{
	const Handler<Object> arg(machine.getArgument());
	bool result;
	if(arg->has("when")){
		result = cast<bool>(arg->getSlot("when"));
	}else{
		result = cast<bool>(arg->index(0));
	}
	if(result){
		machine.pushResult(arg->getSlot("then"));
	}else{
		machine.pushResult(arg->getSlot("else"));
	}
}
DEF_BUILTIN(Object, while_kari)
{
	const Handler<LazyEvalObject> arg(machine.getArgument());
	if(arg){
		const tree::ObjectNode* const node = arg->getRawNode();
		if(node->size() < 2){
			machine.log.w(TAG, 0, "Invalid while_kari.");
			machine.pushResult(arg->getHeap().newUndefinedObject());
			return;
		}
		Handler<Object> obj(arg->getHeap().newUndefinedObject());
		while(cast<bool>(machine.eval(node->index(0)))){
			obj = machine.eval(node->index(1));
		}
		machine.pushResult(obj);
	}else{
		machine.log.w("Machine", 0, "Invalid while_kari");
		machine.pushResult(arg->getHeap().newUndefinedObject());
	}
}
DEF_BUILTIN(Object, lambda)
{
	const Handler<Object> self(machine.getSelf());
	const Handler<LazyEvalObject> arg(machine.getArgument());
	if(!arg || arg->size() < 1){
		machine.log.w(TAG, 0, "Invalid lambda call.");
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	machine.pushResult(self->getHeap().newLambdaObject(machine.getLocal(), arg->getRawNode()->index(0)));
}
DEF_BUILTIN(Object, distance)
{
	const Handler<Object> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	double const x1 = cast<double>(arg->index(0));
	double const y1 = cast<double>(arg->index(1));
	double const x2 = cast<double>(arg->index(2));
	double const y2 = cast<double>(arg->index(3));
	double const dx = x1-x2;
	double const dy = y1-y2;
	machine.pushResult(self->getHeap().newNumericObject( sqrt(dx*dx+dy*dy) ));
}
DEF_BUILTIN(Object, rand)
{
	const Handler<Object> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	std::string txt = cast<std::string>(arg->index(0));
	unsigned int seed = 0;
	const char* str = txt.c_str();
	const size_t max = txt.size();
	for(size_t i = 0;i<max;++i){
		seed += str[i];
	}
	srand(seed);
	machine.pushResult(self->getHeap().newNumericObject( rand() >> 5 ));
}

}
}
