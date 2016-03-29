/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <nekomata/logging/Logging.h>
#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include <cinamo/String.h>

using namespace nekomata::tree;

namespace nekomata{
namespace object{

const std::string TAG("LazyEvalObj");

LazyEvalObject::LazyEvalObject(Object& parent)
:Object(parent, 0), machine(*((machine::Machine*)0)), node(0)
{
	ADD_BUILTIN(clone);
	includeBuitin();
}
LazyEvalObject::LazyEvalObject(Object& parent, const unsigned int hash, machine::Machine& machine, const tree::ObjectNode* const node)
:Object(parent, hash), machine(machine), node(node)
{
	Object::setSlot("$$local", machine.getLocal());
	Object::setSlot("$$self", machine.getSelf());
}

Handler<Object> LazyEvalObject::forceEvalNode(const tree::ExprNode* const node)
{
	machine.enterLocal(Object::getSlot("$$self"), Object::getSlot("$$local"));
	Handler<Object> obj = machine.eval(node);
	machine.endLocal(Object::getSlot("$$self"), Object::getSlot("$$local"));
	return obj;
}
Handler<Object> LazyEvalObject::forceEval(size_t idx)
{
	if(node->has(idx)){
		return forceEvalNode(node->index(idx));
	}else{
		return getHeap().newUndefinedObject();
	}
}
Handler<Object> LazyEvalObject::forceEval(std::string const& name)
{
	if(node->has(name)){
		return forceEvalNode(node->getSlot(name));
	}else{
		return getHeap().newUndefinedObject();
	}
}

/*******************************************************************
 *  INDEXアクセス
 *******************************************************************/
Handler<Object> LazyEvalObject::unshift(const Handler<Object> item)
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support unshift");
	return Handler<Object>(this);
}
Handler<Object> LazyEvalObject::push(const Handler<Object> item)
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support push");
	return Handler<Object>(this);
}
Handler<Object> LazyEvalObject::shift()
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support shift");
	return index(0);
}
Handler<Object> LazyEvalObject::pop()
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support pop");
	return index(size()-1);
}
Handler<Object> LazyEvalObject::index(size_t idx)
{
	if(indexEvalState.count(idx) > 0){
		return Object::index(idx);
	} else if(frozen()) {
		log().w(TAG, &this->node->location(), "Frozen LazyEvalObj does not support lazy evaluation.");
		return getHeap().newUndefinedObject();
	}else{
		const Handler<Object> result(forceEval(idx));
		indexEvalState.insert(std::pair<size_t, bool>(idx, true));
		Object::indexSet(idx, result);
		return result;
	}
}
Handler<Object> LazyEvalObject::indexSet(size_t idx, Handler<Object> item)
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support indexSet");
	return item;
}
size_t LazyEvalObject::size()
{
	return node->size();
}
bool LazyEvalObject::has(size_t idx)
{
	return node->has(idx);
}


/*******************************************************************
 *  KEYアクセス
 *******************************************************************/
Handler<Object> LazyEvalObject::setSlot(std::string const& key, const Handler<Object> value)
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support setSlot");
	return Handler<Object>(this);
}
Handler<Object> LazyEvalObject::getSlot(std::string const& key)
{
	if(slotEvalState.count(key) > 0){ //すでに評価済み
		return Object::getSlot(key);
	} else if(frozen()) {
		log().w(TAG, &this->node->location(), "Frozen LazyEvalObj does not support lazy evaluation.");
		return getHeap().newUndefinedObject();
	}else{ //未評価
		const Handler<Object> result(forceEval(key));
		slotEvalState.insert(std::pair<std::string, bool>(key, true));
		Object::setSlot(key, result);
		return result;
	}
}
bool LazyEvalObject::has(std::string const& key)
{
	return node->has(key);
}
std::vector<std::string> LazyEvalObject::getSlotNames()
{
	return node->getSlotNames();
}
size_t LazyEvalObject::slotSize()
{
	return node->slotSize();
}

std::string LazyEvalObject::toString()
{
	return cinamo::format("<<LazyEvalObject:%d>>", getHash());
}

DEF_BUILTIN(LazyEvalObject, clone)
{
	const Handler<LazyEvalObject> self(machine.getSelf().cast<LazyEvalObject>());
	machine.pushResult( self->getHeap().newUndefinedObject() );
}


}}
