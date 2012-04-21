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

#include <nekomata/logging/Logging.h>
#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include "../util/StringUtil.h"

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
	return util::format("<<LazyEvalObject:%d>>", getHash());
}

DEF_BUILTIN(LazyEvalObject, clone)
{
	const Handler<LazyEvalObject> self(machine.getSelf());
	machine.pushResult( self->getHeap().newUndefinedObject() );
}


}}
