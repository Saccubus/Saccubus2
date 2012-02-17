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
int LazyEvalObject::push(Object* const item)
{
	/* セットはできない。アクセスだけ。 */
	return 0;
}
Object* LazyEvalObject::setIndex(size_t idx, Object* obj)
{
	/* セットはできない。アクセスだけ。 */
	return obj;
}
Object* LazyEvalObject::getIndex(size_t idx)
{
	if(Object::hasIndex(idx)){
		return Object::getIndex(idx);
	}else if(node->hasNode(idx)){
		const ExprNode* const expr = node->getNode(idx);
		Object* const result = machine.eval(expr);
		return setIndex(idx, result);
	}else{
		return getHeap().newUndefinedObject();
	}
}
bool LazyEvalObject::hasIndex(size_t idx)
{
	return node->hasNode(idx);
}
size_t LazyEvalObject::getIndexSize()
{
	return node->getIndexedNodeSize();
}

/*******************************************************************
 *  KEYアクセス
 *******************************************************************/
Object* LazyEvalObject::setSlot(const std::string& name, Object* const item)
{
	/* セットはできない。アクセスだけ。 */
	return item;
}
Object* LazyEvalObject::getSlot(const std::string& name)
{
	if(Object::hasSlot(name)){ //すでに評価済み
		return Object::getSlot(name);
	}else if(node->hasNode(name)){ //未評価
		const ExprNode* const expr = node->getNode(name);
		Object* const result = machine.eval(expr);
		return Object::setSlot(name, result);
	}else{
		return getHeap().newUndefinedObject();
	}
}
bool LazyEvalObject::hasSlot(const std::string& name)
{
	return node->hasNode(name);
}
std::vector<std::string> LazyEvalObject::getSlotNames()
{
	return node->getNodeNames();
}

}



