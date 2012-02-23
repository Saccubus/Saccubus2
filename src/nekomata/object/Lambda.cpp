/*
 * Lambda.cpp
 *
 *  Created on: 2012/02/19
 *      Author: psi
 */

#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"

namespace nekomata{
namespace object{

LambdaObject::LambdaObject(ObjectHeap& heap)
:MethodObject(heap), builtins(new BuiltinMethods()), node(0)
{
	ADD_BUILTIN(builtins, heap, index);
	includeBuitin(builtins);
}
LambdaObject::LambdaObject(LambdaObject& parent, const unsigned int hash, Object* const scope, const tree::Node* const node)
:MethodObject(parent, hash), builtins(0),node(node)
{
	Object::setSlot("$$scope", scope);
}

LambdaObject::~LambdaObject(){
	if(builtins){
		delete builtins;
	}
}
void LambdaObject::_method_index(NativeMethodObject* method, machine::Machine& machine)
{
	LambdaObject* const self = dynamic_cast<LambdaObject*>(machine.getSelf());
	Object* const local = self->getHeap().newLambdaScopeObject(machine.getArgument());
	machine.enterLocal(local, self->Object::getSlot("$$scope"));
	machine.pushResult(machine.eval(self->node));
	machine.endLocal(local);
}

LambdaScopeObject::LambdaScopeObject(ObjectHeap& heap)
:Object(heap), builtins(new BuiltinMethods())
{
	ADD_BUILTIN_ALT(builtins, heap, "@", atmark);
	includeBuitin(builtins);
}

LambdaScopeObject::LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, Object* const arg)
:Object(parent, hash), builtins(0)
{
	Object::setSlot("$$arg", arg);
}
LambdaScopeObject::~LambdaScopeObject()
{
	if(builtins){
		delete builtins;
	}
}
void LambdaScopeObject::_method_atmark(NativeMethodObject* method, machine::Machine& machine)
{
	LazyEvalObject* const mergeArg = dynamic_cast<LazyEvalObject*>(machine.getArgument());
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
