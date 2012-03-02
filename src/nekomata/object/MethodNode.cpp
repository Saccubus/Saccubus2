/*
 * MethodNode.cpp
 *
 *  Created on: 2012/02/17
 *      Author: psi
 */

#include <vector>
#include <sstream>
#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"

namespace nekomata{
namespace object{
MethodNodeObject::MethodNodeObject(Object& parent, const unsigned int hash, Handler<Object> const scope, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList)
:MethodObject(parent, hash), node(node),argList(argList), rule(rule)
{
	Object::setSlot("$$scope", scope);
}
MethodNodeObject::MethodNodeObject(Object& parent, const unsigned int hash, Handler<Object> const scope, const tree::Node* const node, LocalScopeRule rule)
:MethodObject(parent, hash), node(node),rule(rule)
{
	Object::setSlot("$$scope", scope);
}
MethodNodeObject::~MethodNodeObject()
{

}
void MethodNodeObject::mergeArg(machine::Machine& machine, Handler<Object> const local, Handler<Object> const arg)
{
	switch(rule)
	{
	case def:
	{
		size_t idx = 0;
		for(std::vector<std::string>::const_iterator it = argList.begin();it!=argList.end();++it){
			Handler<Object> const obj = arg->index(idx);
			local->setSlot((*it), obj);
			++idx;
		}
	}
		break;
	case def_kari:
	{
		std::stringstream ss;
		size_t idx=0;
		while(arg->has(idx)){
			ss.str("");
			ss << "$" << (idx+1);
			local->setSlot(ss.str(), arg->index(idx));
		}
		std::vector<std::string> names = arg->getSlotNames();
		for(std::vector<std::string>::const_iterator it = names.begin();it!=names.end();++it){
			ss.str("");
			ss << "$" << (*it);
			local->setSlot(ss.str(), arg->getSlot(*it));
		}
	}
		break;
	default:
		break;
	}
}

void MethodNodeObject::eval(machine::Machine& machine)
{
	const Handler<Object> origLocal = machine.getLocal();
	const Handler<Object> arg = machine.getArgument();

	const Handler<Object> local = getHeap().newRawObject();
	machine.enterLocal(local, Object::getSlot("$$scope"));
	{
		machine.enterLocal(origLocal);
		mergeArg(machine, local, arg);
		machine.endLocal(origLocal);
	}
	machine.pushResult(machine.eval(this->node));
	machine.endLocal(local);
}

}
}
