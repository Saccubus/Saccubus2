/*
 * Object.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "../Machine.h"
#include <math.h>
#include <sstream>
#include <algorithm>
#include <tr1/functional>

namespace machine
{

Object::Object(ObjectHeap& heap, const unsigned int hash)
:heap(heap), hash(hash)
{
	// TODO Auto-generated constructor stub

}

Object::~Object()
{
	// TODO Auto-generated destructor stub
}

void Object::eval(Machine& machine){
	machine.pushResult(this);
}

Object* Object::unshift(Object* const item)
{
	objectList.insert(objectList.begin(), item);
	return this;
}
Object* Object::push(Object* const item)
{
	objectList.push_back(item);
	return this;
}
Object* Object::shift()
{
	if(Object::size() > 0){
		Object* const obj = objectList.front();
		objectList.erase(objectList.begin());
		return obj;
	}else{
		return heap.newUndefinedObject();
	}
}
Object* Object::pop()
{
	if(Object::size() > 0){
		Object* const obj = objectList.back();
		objectList.pop_back();
		return obj;
	}else{
		return heap.newUndefinedObject();
	}
}
Object* Object::index(size_t idx)
{
	if(Object::has(idx)){
		return objectList.at(idx);
	}else{
		return heap.newUndefinedObject();
	}
}
Object* Object::indexSet(size_t idx, Object* item)
{
	if(idx < objectList.size()){
		objectList[idx] = item;
	}else{
		objectList.insert(objectList.end(), idx-objectList.size(), getHeap().newUndefinedObject());
		objectList.push_back(item);
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
	for(MapIterator it = objectMap.begin(); it != objectMap.end(); ++it){
		slotList.push_back(it->first);
	}
	return slotList;
}

bool Object::isUndefined(){
	return false;
}
Object* Object::setSlot(const std::string& name, Object* const item)
{
	objectMap.erase(name);
	objectMap.insert(MapPair(name, item));
	return this;
}
Object* Object::getSlot(const std::string& name){
	MapIterator it = objectMap.find(name);
	if(it == objectMap.end()){
		return getHeap().newUndefinedObject();
	}else{
		return it->second;
	}
}

size_t Object::slotSize()
{
	return objectMap.size();
}


StringObject* Object::toStringObject()
{
	std::stringstream ss;
	ss << "<< Object: " << getHash() << ">> {";
	for(MapIterator it = objectMap.begin();it != objectMap.end();++it){
		ss << std::endl << it->first << " : " << it->second->toStringObject()->toString();
	}
	int cnt=0;
	for(Iterator it = objectList.begin();it != objectList.end();++it){
		ss << std::endl << "$" << cnt << " : " << (*it)->toStringObject()->toString();
		++cnt;
	}
	ss << "}";
	return getHeap().newStringObject(ss.str());
}
NumericObject* Object::toNumericObject()
{
	return getHeap().newNumericObject(NAN);
}
BooleanObject* Object::toBooleanObject()
{
	return getHeap().newBooleanObject(true);
}

void Object::inject(Object* to){
	to->objectList.insert(to->objectList.end(), objectList.begin(), objectList.end());
	to->objectMap.insert(objectMap.begin(), objectMap.end());
}

//---------------------------------------------------------------------------------------------------------------------
// メソッド
//---------------------------------------------------------------------------------------------------------------------

void Object::_method_def(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	LazyEvalObject* const arg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
	if(!arg || arg->size() < 2){
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	const tree::InvokeNode* const invokeNode = dynamic_cast<const tree::InvokeNode*>(arg->getRawNode()->index(0));
	const tree::BindNode* const bindNode = dynamic_cast<const tree::BindNode*>(arg->getRawNode()->index(0));
	if(invokeNode){
		MethodNodeObject* const _method = self->getHeap().newMethodNodeObject(arg->getRawNode()->index(1), MethodNodeObject::def);
		self->setSlot(invokeNode->getMessageName(), _method);
		machine.pushResult(_method);
	}else if(bindNode){
		const tree::InvokeNode* const nameNode = dynamic_cast<const tree::InvokeNode*>(bindNode->getExprNode());
		if(!nameNode){
			machine.pushResult(self->getHeap().newUndefinedObject());
			return;
		}
		std::vector<std::string> argList=bindNode->getObjectNode()->getSlotNames();
		MethodNodeObject* const _method = self->getHeap().newMethodNodeObject(arg->getRawNode()->index(1), MethodNodeObject::def, argList);
		self->setSlot(nameNode->getMessageName(), _method);
		machine.pushResult(_method);
	}else{
		machine.pushResult(self->getHeap().newUndefinedObject());
	}
}
void Object::_method_def_kari(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	LazyEvalObject* const arg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
	if(!arg || !arg->size() < 2){
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	std::string methodName = arg->index(0)->toStringObject()->toString();
	MethodNodeObject* const _method = self->getHeap().newMethodNodeObject(arg->getRawNode()->index(1), MethodNodeObject::def_kari);
	self->setSlot(methodName, _method);
	machine.pushResult(_method);
}

void Object::_method_index(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->index(static_cast<size_t>(machine.getArgument()->index(0)->toNumericObject()->toNumeric())));
}
void Object::_method_indexSet(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	Object* const arg = machine.getArgument();
	size_t const idx = static_cast<size_t>(arg->index(0)->toNumericObject()->toNumeric());
	machine.pushResult(self->indexSet(idx, arg->index(1)));
}
void Object::_method_size(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->getHeap().newNumericObject(self->size()));
}
void Object::_method_unshift(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->unshift(machine.getArgument()->index(0)));
}
void Object::_method_push(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->push(machine.getArgument()->index(0)));
}
void Object::_method_shift(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->shift());
}
void Object::_method_pop(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->pop());
}

bool Object::_sort_func(Machine& machine, Object* const self, Object* const other)
{
	Object* result = machine.send(self, "lessThan", self->getHeap().newArray(other, 0));
	return result->toBooleanObject()->toBool();
}

void Object::_method_sort(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	std::sort(self->objectList.begin(), self->objectList.end(),std::tr1::bind(&Object::_sort_func, machine, std::tr1::placeholders::_1, std::tr1::placeholders::_2));
	machine.pushResult(self);
}
void Object::_method_sum(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	double result = 0.0;
	const size_t max = self->size();
	for(size_t i=0;i<max;++i){
		result += self->index(i)->toNumericObject()->toNumeric();
	}
	machine.pushResult(self->getHeap().newNumericObject(result));
}
void Object::_method_product(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	double result = 1.0;
	const size_t max = self->size();
	for(size_t i=0;i<max;++i){
		result *= self->index(i)->toNumericObject()->toNumeric();
	}
	machine.pushResult(self->getHeap().newNumericObject(result));
}
void Object::_method_join(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	std::stringstream ss;
	Object* const arg = machine.getArgument();
	const size_t max = self->size();
	if(max <= 0){
		machine.pushResult(self->getHeap().newStringObject(""));
		return;
	}
	std::string sep = arg->index(0)->toStringObject()->toString();
	ss << self->index(0)->toStringObject()->toString();
	for(size_t i=1;i<max;++i){
		ss << sep << self->index(i)->toStringObject()->toString();
	}
	machine.pushResult(self->getHeap().newStringObject(ss.str()));
}


void Object::_method_setSlot(NativeMethodObject* method, Machine& machine)
{
	Object* const arg = machine.getArgument();
	Object* const self = machine.getSelf();
	std::string name = arg->index(0)->toStringObject()->toString();
	Object* const obj = arg->index(1);
	machine.pushResult(self->setSlot(name, obj));
}
void Object::_method_getSlot(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
	std::string name = machine.getArgument()->index(0)->toStringObject()->toString();
	Object* const obj = self->getSlot(name);
	machine.pushResult(obj);
}
void Object::_method_clone(NativeMethodObject* method, Machine& machine){
	Object* const self = machine.getSelf();
}

void Object::_method_if(NativeMethodObject* method, Machine& machine)
{
	Object* const arg = machine.getArgument();
	bool result;
	if(arg->has("when")){
		result = arg->getSlot("when")->toBooleanObject()->toBool();
	}else{
		result = arg->index(0)->toBooleanObject()->toBool();
	}
	if(result){
		machine.pushResult(arg->getSlot("then"));
	}else{
		machine.pushResult(arg->getSlot("else"));
	}
}
void Object::_method_while_kari(NativeMethodObject* method, Machine& machine)
{
	LazyEvalObject* const arg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
	if(arg){
		const tree::ObjectNode* const node = arg->getRawNode();
		if(node->size() < 2){
			machine.pushResult(arg->getHeap().newUndefinedObject());
			return;
		}
		Object* obj = arg->getHeap().newUndefinedObject();
		while(machine.eval(node->index(0))->toBooleanObject()->toBool()){
			obj = machine.eval(node->index(1));
		}
		machine.pushResult(obj);
	}else{
		machine.log.w("Machine", 0, "Invalid while_kari");
		machine.pushResult(arg->getHeap().newUndefinedObject());
	}
}
void Object::_method_lambda(NativeMethodObject* method, Machine& machine)
{
	Object* const self = machine.getSelf();
}

}
 /* namespace machine */
