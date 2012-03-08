/*
 * LazyEval.cpp
 *
 *  Created on: 2012/02/17
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include "../util/StringUtil.h"

using namespace nekomata::tree;

namespace nekomata{
namespace object{

const std::string TAG("LazyEvalObj");

LazyEvalObject::LazyEvalObject(Object& parent, const unsigned int hash, machine::Machine& machine, const tree::ObjectNode* const node)
:Object(parent, hash), machine(machine), node(node){
}
LazyEvalObject::~LazyEvalObject(){

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
	}else if(node->has(idx)){
		const ExprNode* const expr = node->index(idx);
		const Handler<Object> result(machine.eval(expr));
		indexEvalState.insert(std::pair<size_t, bool>(idx, true));
		Object::indexSet(idx, result);
		return result;
	}else{
		return getHeap().newUndefinedObject();
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
Handler<Object> LazyEvalObject::setSlot(const std::string& key, const Handler<Object> value)
{
	/* セットはできない。アクセスだけ。 */
	log().w(TAG, &this->node->location(), "LazyEvalObj does not support setSlot");
	return Handler<Object>(this);
}
Handler<Object> LazyEvalObject::getSlot(const std::string& key)
{
	if(slotEvalState.count(key) > 0){ //すでに評価済み
		return Object::getSlot(key);
	} else if(frozen()) {
		log().w(TAG, &this->node->location(), "Frozen LazyEvalObj does not support lazy evaluation.");
		return getHeap().newUndefinedObject();
	}else if(node->has(key)){ //未評価
		const ExprNode* const expr = node->getSlot(key);
		const Handler<Object> result(machine.eval(expr));
		slotEvalState.insert(std::pair<std::string, bool>(key, true));
		Object::setSlot(key, result);
		return result;
	}else{
		return getHeap().newUndefinedObject();
	}
}
bool LazyEvalObject::has(const std::string& key)
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
	return util::format("<< LazyEvalObject %d >>", getHash());
}

}}
