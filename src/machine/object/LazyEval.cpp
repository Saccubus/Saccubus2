/*
 * LazyEval.cpp
 *
 *  Created on: 2012/02/17
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include "../Machine.h"
#include "../../tree/Node.h"

using namespace tree;

namespace machine{
LazyEvalObject::LazyEvalObject(ObjectHeap& heap, const unsigned int hash, Machine& machine, const ObjectNode* const node)
:Object(heap, hash), machine(machine), node(node){
}
LazyEvalObject::~LazyEvalObject(){

}
/*******************************************************************
 *  INDEXアクセス
 *******************************************************************/
Object* LazyEvalObject::unshift(Object* const item)
{
	/* セットはできない。アクセスだけ。 */
	return this;
}
Object* LazyEvalObject::push(Object* const item)
{
	/* セットはできない。アクセスだけ。 */
	return this;
}
Object* LazyEvalObject::shift()
{
	/* セットはできない。アクセスだけ。 */
	return index(0);
}
Object* LazyEvalObject::pop()
{
	/* セットはできない。アクセスだけ。 */
	return index(size()-1);
}
Object* LazyEvalObject::index(size_t idx)
{
	if(Object::has(idx)){
		return Object::index(idx);
	}else if(node->has(idx)){
		const ExprNode* const expr = node->index(idx);
		Object* const result = machine.eval(expr);
		return indexSet(idx, result);
	}else{
		return getHeap().newUndefinedObject();
	}
}
Object* LazyEvalObject::indexSet(size_t idx, Object* item)
{
	/* セットはできない。アクセスだけ。 */
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
Object* LazyEvalObject::setSlot(const std::string& key, Object* const value)
{
	/* セットはできない。アクセスだけ。 */
	return this;
}
Object* LazyEvalObject::getSlot(const std::string& key)
{
	if(Object::has(key)){ //すでに評価済み
		return Object::getSlot(key);
	}else if(node->has(key)){ //未評価
		const ExprNode* const expr = node->getSlot(key);
		Object* const result = machine.eval(expr);
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


}



