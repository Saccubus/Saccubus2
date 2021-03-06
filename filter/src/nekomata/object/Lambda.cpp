/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <sstream>
#include <nekomata/logging/Exception.h>
#include <cinamo/String.h>

#include "Object.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"

namespace nekomata{
namespace object{

LambdaObject::LambdaObject(ObjectHeap& heap)
:MethodObject(heap), node(0)
{
	ADD_BUILTIN(index);
	includeBuitin();
}
LambdaObject::LambdaObject(LambdaObject& parent, const unsigned int hash, const Handler<Object> scope, const tree::Node* const node)
:MethodObject(parent, hash), node(node)
{
	Object::setSlot("$$scope", scope);
}

DEF_BUILTIN(LambdaObject, index)
{
	const Handler<LambdaObject> self(machine.getSelf().cast<LambdaObject>());
	if(!self){
		throw  logging::Exception(__FILE__, __LINE__, "Invalid Lambda Object!!");
	}
	const Handler<Object> local = self->getHeap().newLambdaScopeObject(machine.getArgument());

	const Handler<Object> arg = machine.getArgument();
	std::stringstream ss;
	size_t idx=0;
	while(arg->has(idx)){
		ss.str("");
		ss << "@" << idx;
		local->setSlot(ss.str(), arg->index(idx));
		++idx;
	}
	std::vector<std::string> names = arg->getSlotNames();
	for(std::vector<std::string>::const_iterator it = names.begin();it!=names.end();++it){
		std::string const& str = *it;
		ss.str("");
		ss << "@" << (*it);
		local->setSlot(ss.str(), arg->getSlot(str));
	}

	machine.enterLocal(machine.getSelf(), local, self->Object::getSlot("$$scope"));
	machine.pushResult(machine.eval(self->node));
	machine.endLocal(machine.getSelf(), local);
}

std::string LambdaObject::toString()
{
	return cinamo::format("<<LambdaObject:%d>>", getHash());
}

LambdaScopeObject::LambdaScopeObject(Object& parent)
:Object(parent, 0)
{
	ADD_BUILTIN_ALT(atmark, "@");
	includeBuitin();
}

LambdaScopeObject::LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, const Handler<Object> arg)
:Object(parent, hash)
{
	Object::setSlot("$$arg", arg);
}
DEF_BUILTIN(LambdaScopeObject, atmark)
{
	const Handler<LazyEvalObject> mergeArg(machine.getArgument().cast<LazyEvalObject>());
	if(!mergeArg){
		throw  logging::Exception(__FILE__, __LINE__, "Invalid Lambda Object!! Argument is not LazyEvalObject");
	}
	const Handler<Object> local = machine.getLocal();
	const Handler<Object> arg = machine.getSelf()->getSlot("$$arg");
	size_t const max = mergeArg->getRawNode()->size();
	for(size_t i=0;i<max;++i){
		const tree::InvokeNode* argNode = dynamic_cast<const tree::InvokeNode*>(mergeArg->getRawNode()->index(i));
		if(argNode){
			local->setSlot(argNode->getMessageName(), arg->index(i));
		}
	}
	machine.pushResult(local);
}

std::string LambdaScopeObject::toString()
{
	return cinamo::format("<<LambdaScopeObject:%d>>", getHash());
}

}}
