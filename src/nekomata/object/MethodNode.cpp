/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <vector>
#include <sstream>
#include <nekomata/logging/Logging.h>
#include <nekomata/logging/Exception.h>
#include <cinamo/String.h>

#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"

namespace nekomata{
namespace object{

static const std::string TAG("MethodNodeObject");

MethodNodeObject::MethodNodeObject(Object& parent, const unsigned int hash, const Handler<Object> scope, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList)
:MethodObject(parent, hash), node(node),argList(argList), rule(rule)
{
	Object::setSlot("$$scope", scope);
}
MethodNodeObject::MethodNodeObject(Object& parent, const unsigned int hash, const Handler<Object> scope, const tree::Node* const node, LocalScopeRule rule)
:MethodObject(parent, hash), node(node),rule(rule)
{
	Object::setSlot("$$scope", scope);
}
void MethodNodeObject::mergeArg(machine::Machine& machine, const Handler<Object> local, const Handler<Object> arg)
{
	machine.log.t(TAG, 0, "merging method arguments.");
	switch(rule)
	{
	case def:
	{
		size_t idx = 0;
		for(std::vector<std::string>::const_iterator it = argList.begin();it!=argList.end();++it){
			const Handler<Object> obj = arg->index(idx);
			local->setSlot((*it), obj);
			++idx;
			machine.log.t(TAG, 0, "set %s => %s", it->c_str(), obj->toString().c_str());
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
			std::string name = ss.str();
			local->setSlot(ss.str(), arg->index(idx));
			//machine.log.t(TAG, 0, "set %s => %s", ss.str().c_str(), arg->index(idx)->toString().c_str());
			++idx;
		}
		std::vector<std::string> names = arg->getSlotNames();
		for(std::vector<std::string>::const_iterator it = names.begin();it!=names.end();++it){
			ss.str("");
			ss << "$" << (*it);
			local->setSlot(ss.str(), arg->getSlot(*it));
			//machine.log.t(TAG, 0, "set %s => %s", ss.str().c_str(), arg->index(idx)->toString().c_str());
		}
	}
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon rule type: %d", rule);
	}
}

void MethodNodeObject::eval(machine::Machine& machine)
{
	const Handler<Object> origLocal = machine.getLocal();
	const Handler<Object> arg = machine.getArgument();

	const Handler<Object> local = getHeap().newRawObject();
	machine.enterLocal(machine.getSelf(), local, Object::getSlot("$$scope"));
	{
		machine.enterLocal(machine.getSelf(), origLocal);
		mergeArg(machine, local, arg);
		machine.endLocal(machine.getSelf(), origLocal);
	}
	machine.pushResult(machine.eval(this->node));
	machine.endLocal(machine.getSelf(), local);
}

std::string MethodNodeObject::toString()
{
	return cinamo::format("<<MethodNodeObject:%d>>", getHash());
}


}}
