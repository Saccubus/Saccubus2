/*
 * Lambda.cpp
 *
 *  Created on: 2012/02/19
 *      Author: psi
 */

#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include "../logging/Exception.h"

namespace nekomata{
namespace object{

LambdaObject::LambdaObject(ObjectHeap& heap)
:MethodObject(heap), node(0)
{
	ADD_BUILTIN(index);
	includeBuitin();
}
LambdaObject::LambdaObject(LambdaObject& parent, const unsigned int hash, Object* const scope, const tree::Node* const node)
:MethodObject(parent, hash), node(node)
{
	Object::setSlot("$$scope", scope);
}

LambdaObject::~LambdaObject(){
}
DEF_BUILTIN(LambdaObject, index)
{
	LambdaObject* const self = dynamic_cast<LambdaObject*>(machine.getSelf());
	if(!self){
		throw  logging::Exception(__FILE__, __LINE__, "Invalid Lambda Object!!");
	}
	Object* const local = self->getHeap().newLambdaScopeObject(machine.getArgument());
	machine.enterLocal(local, self->Object::getSlot("$$scope"));
	machine.pushResult(machine.eval(self->node));
	machine.endLocal(local);
}

LambdaScopeObject::LambdaScopeObject(ObjectHeap& heap)
:Object(heap)
{
	ADD_BUILTIN_ALT(atmark, "alt");
	includeBuitin();
}

LambdaScopeObject::LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, Object* const arg)
:Object(parent, hash)
{
	Object::setSlot("$$arg", arg);
}
LambdaScopeObject::~LambdaScopeObject()
{
}
DEF_BUILTIN(LambdaScopeObject, atmark)
{
	LazyEvalObject* const mergeArg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
	if(!mergeArg){
		throw  logging::Exception(__FILE__, __LINE__, "Invalid Lambda Object!! Argument is not LazyEvalObject");
	}
	Object* const local = machine.getLocal();
	Object* const arg = machine.getSelf()->getSlot("$$arg");
	size_t const max = mergeArg->getRawNode()->size();
	for(size_t i=0;i<max;++i){
		const tree::InvokeNode* argNode = dynamic_cast<const tree::InvokeNode*>(mergeArg->getRawNode()->index(i));
		if(argNode){
			local->setSlot(argNode->getMessageName(), arg->index(i));
		}
	}
	machine.pushResult(local);
}

}
}
