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
#include "../Machine.h"
#include "../../tree/Node.h"

namespace machine{
MethodNodeObject::MethodNodeObject(ObjectHeap& heap, const unsigned int hash, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList)
:MethodObject(heap, hash), node(node),argList(argList), rule(rule)
{
}
MethodNodeObject::MethodNodeObject(ObjectHeap& heap, const unsigned int hash, const tree::Node* const node, LocalScopeRule rule)
:MethodObject(heap, hash), node(node),rule(rule)
{
}
MethodNodeObject::~MethodNodeObject()
{

}
void MethodNodeObject::mergeArg(Machine& machine, Object* const local, Object* const arg)
{
	switch(rule)
	{
	case def:
	{
		size_t idx = 0;
		for(std::vector<std::string>::const_iterator it = argList.begin();it!=argList.end();++it){
			local->setSlot((*it), arg->getIndex(idx));
			++idx;
		}
	}
		break;
	case def_kari:
	{
		std::stringstream ss;
		size_t idx=0;
		while(arg->hasIndex(idx)){
			ss.str("");
			ss << "$" << (idx+1);
			local->setSlot(ss.str(), arg->getIndex(idx));
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

void MethodNodeObject::eval(Machine& machine)
{
	Object* const local = machine.newLocal();
	mergeArg(machine, local, machine.getArgument());
	machine.pushResult(machine.eval(this->node));
	machine.endLocal(local);
}

}
