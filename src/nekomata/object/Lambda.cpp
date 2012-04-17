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

#include <nekomata/logging/Exception.h>

#include "Object.h"
#include "../util/StringUtil.h"
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

LambdaObject::~LambdaObject(){
}
DEF_BUILTIN(LambdaObject, index)
{
	const Handler<LambdaObject> self(machine.getSelf());
	if(!self){
		throw  logging::Exception(__FILE__, __LINE__, "Invalid Lambda Object!!");
	}
	const Handler<Object> local = self->getHeap().newLambdaScopeObject(machine.getArgument());
	machine.enterLocal(local, self->Object::getSlot("$$scope"));
	machine.pushResult(machine.eval(self->node));
	machine.endLocal(local);
}

std::string LambdaObject::toString()
{
	return util::format("<<LambdaObject:%d>>", getHash());
}

LambdaScopeObject::LambdaScopeObject(ObjectHeap& heap)
:Object(heap)
{
	ADD_BUILTIN_ALT(atmark, "alt");
	includeBuitin();
}

LambdaScopeObject::LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, const Handler<Object> arg)
:Object(parent, hash)
{
	Object::setSlot("$$arg", arg);
}
LambdaScopeObject::~LambdaScopeObject()
{
}
DEF_BUILTIN(LambdaScopeObject, atmark)
{
	const Handler<LazyEvalObject> mergeArg(machine.getArgument());
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
	return util::format("<<LambdaScopeObject:%d>>", getHash());
}

}}
