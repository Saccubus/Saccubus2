/*
 * Object.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include <math.h>
#include <sstream>
#include <algorithm>
#include <tr1/functional>

namespace nekomata{
namespace object
{
Object::Object(ObjectHeap& heap)
:heap(heap), hash(-1), color(0), builtins(0)
{
}
Object::Object(ObjectHeap& heap, bool isRaw)
:heap(heap), hash(-1), color(0), builtins(new BuiltinMethods())
{
	ADD_BUILTIN(builtins, heap, setSlot);
	ADD_BUILTIN(builtins, heap, getSlot);
	ADD_BUILTIN(builtins, heap, clone);
	if(!isRaw){
		ADD_BUILTIN(builtins, heap, def);
		ADD_BUILTIN(builtins, heap, def_kari);

		ADD_BUILTIN(builtins, heap, index);
		ADD_BUILTIN(builtins, heap, indexSet);
		ADD_BUILTIN(builtins, heap, size);
		ADD_BUILTIN(builtins, heap, unshift);
		ADD_BUILTIN(builtins, heap, push);
		ADD_BUILTIN(builtins, heap, shift);
		ADD_BUILTIN(builtins, heap, pop);
		ADD_BUILTIN(builtins, heap, sort);
		ADD_BUILTIN(builtins, heap, sum);
		ADD_BUILTIN(builtins, heap, product);
		ADD_BUILTIN(builtins, heap, join);

		ADD_BUILTIN(builtins, heap, if);
		ADD_BUILTIN(builtins, heap, while_kari);
		ADD_BUILTIN(builtins, heap, lambda);

		ADD_BUILTIN(builtins, heap, distance);
		ADD_BUILTIN(builtins, heap, rand);
	}
	includeBuitin(builtins);
}
Object::Object(Object& parent, const unsigned int hash)
:heap(parent.getHeap()), hash(hash), color(0), builtins(0)
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

void Object::includeBuitin(BuiltinMethods* methods)
{
	for(BuiltinMethods::iterator it = methods->begin(); it!=methods->end();++it){
		Object::setSlot(it->first, &it->second);
	}
}

void Object::eval(machine::Machine& machine){
	machine.pushResult(this);
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

int Object::getColor(){
	return this->color;
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
	for(SlotMapIterator it = objectMap.begin(); it != objectMap.end(); ++it){
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
	objectMap.insert(SlotMapPair(name, item));
	return this;
}
Object* Object::getSlot(const std::string& name){
	SlotMapIterator it = objectMap.find(name);
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
	for(SlotMapIterator it = objectMap.begin();it != objectMap.end();++it){
		ss << std::endl << it->first << " : " << "<<Object"<< it->second->getHash() <<">>";
	}
	int cnt=0;
	for(SlotListIterator it = objectList.begin();it != objectList.end();++it){
		ss << std::endl << "$" << cnt << " : " << (*it)->getHash();
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

//---------------------------------------------------------------------------------------------------------------------
// メソッド
//---------------------------------------------------------------------------------------------------------------------

void Object::_method_def(NativeMethodObject* method, machine::Machine& machine)
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
		MethodNodeObject* const _method = self->getHeap().newMethodNodeObject(machine.getLocal(), arg->getRawNode()->index(1), MethodNodeObject::def);
		self->setSlot(invokeNode->getMessageName(), _method);
		machine.pushResult(_method);
	}else if(bindNode){
		const tree::InvokeNode* const nameNode = dynamic_cast<const tree::InvokeNode*>(bindNode->getExprNode());
		if(!nameNode){
			machine.pushResult(self->getHeap().newUndefinedObject());
			return;
		}
		std::vector<std::string> argList=bindNode->getObjectNode()->getSlotNames();
		MethodNodeObject* const _method = self->getHeap().newMethodNodeObject(machine.getLocal(), arg->getRawNode()->index(1), MethodNodeObject::def, argList);
		self->setSlot(nameNode->getMessageName(), _method);
		machine.pushResult(_method);
	}else{
		machine.pushResult(self->getHeap().newUndefinedObject());
	}
}
void Object::_method_def_kari(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	LazyEvalObject* const arg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
	if(!arg || arg->size() < 2){
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	std::string methodName = arg->index(0)->toStringObject()->toString();
	MethodNodeObject* const _method = self->getHeap().newMethodNodeObject(machine.getLocal(), arg->getRawNode()->index(1), MethodNodeObject::def_kari);
	self->setSlot(methodName, _method);
	machine.pushResult(_method);
}

void Object::_method_index(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->index(static_cast<size_t>(machine.getArgument()->index(0)->toNumericObject()->toNumeric())));
}
void Object::_method_indexSet(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	Object* const arg = machine.getArgument();
	size_t const idx = static_cast<size_t>(arg->index(0)->toNumericObject()->toNumeric());
	machine.pushResult(self->indexSet(idx, arg->index(1)));
}
void Object::_method_size(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->getHeap().newNumericObject(self->size()));
}
void Object::_method_unshift(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->unshift(machine.getArgument()->index(0)));
}
void Object::_method_push(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->push(machine.getArgument()->index(0)));
}
void Object::_method_shift(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->shift());
}
void Object::_method_pop(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	machine.pushResult(self->pop());
}

bool Object::_sort_func(machine::Machine& machine, Object* const self, Object* const other)
{
	Object* result = machine.send(self, "lessThan", self->getHeap().newArray(other, 0));
	return result->toBooleanObject()->toBool();
}

void Object::_method_sort(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	std::sort(self->objectList.begin(), self->objectList.end(),std::tr1::bind(&Object::_sort_func, machine, std::tr1::placeholders::_1, std::tr1::placeholders::_2));
	machine.pushResult(self);
}
void Object::_method_sum(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	double result = 0.0;
	const size_t max = self->size();
	for(size_t i=0;i<max;++i){
		result += self->index(i)->toNumericObject()->toNumeric();
	}
	machine.pushResult(self->getHeap().newNumericObject(result));
}
void Object::_method_product(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	double result = 1.0;
	const size_t max = self->size();
	for(size_t i=0;i<max;++i){
		result *= self->index(i)->toNumericObject()->toNumeric();
	}
	machine.pushResult(self->getHeap().newNumericObject(result));
}
void Object::_method_join(NativeMethodObject* method, machine::Machine& machine)
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


void Object::_method_setSlot(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const arg = machine.getArgument();
	Object* const self = machine.getSelf();
	std::string name = arg->index(0)->toStringObject()->toString();
	Object* const obj = arg->index(1);
	machine.pushResult(self->setSlot(name, obj));
}
void Object::_method_getSlot(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	std::string name = machine.getArgument()->index(0)->toStringObject()->toString();
	Object* const obj = self->getSlot(name);
	machine.pushResult(obj);
}
void Object::_method_clone(NativeMethodObject* method, machine::Machine& machine){
	Object* const self = machine.getSelf();
}

void Object::_method_if(NativeMethodObject* method, machine::Machine& machine)
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
void Object::_method_while_kari(NativeMethodObject* method, machine::Machine& machine)
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
void Object::_method_lambda(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	LazyEvalObject* const arg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
	if(!arg || arg->size() < 1){
		machine.pushResult(self->getHeap().newUndefinedObject());
		return;
	}
	machine.pushResult(self->getHeap().newLambdaObject(machine.getLocal(), arg->getRawNode()->index(0)));
}
void Object::_method_distance(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	Object* const arg = machine.getArgument();
	double const x1 = arg->index(0)->toNumericObject()->toNumeric();
	double const y1 = arg->index(1)->toNumericObject()->toNumeric();
	double const x2 = arg->index(2)->toNumericObject()->toNumeric();
	double const y2 = arg->index(3)->toNumericObject()->toNumeric();
	double const dx = x1-x2;
	double const dy = y1-y2;
	machine.pushResult(self->getHeap().newNumericObject( sqrt(dx*dx+dy*dy) ));
}
void Object::_method_rand(NativeMethodObject* method, machine::Machine& machine)
{
	Object* const self = machine.getSelf();
	Object* const arg = machine.getArgument();
	std::string txt = arg->index(0)->toStringObject()->toString();
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
