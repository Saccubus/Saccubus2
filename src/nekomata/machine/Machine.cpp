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

#include <tr1/memory>
#include <nekomata/logging/Logging.h>

#include "Machine.h"
#include "../object/Object.h"
#include "../object/Cast.h"
#include "../object/Heap.h"
#include "../tree/Node.h"

using namespace nekomata::tree;
using std::tr1::shared_ptr;

namespace nekomata{
namespace machine{

static const std::string TAG("Machine");

Machine::Machine(logging::Logger& log, system::System& system)
:RootHolder()
,heap(log, system, *this)
,log(log)
{
	selfStack.push(heap.getSystemObject().get());
	this->enterLocal(heap.getSystemObject(), heap.newUndefinedObject());
	rootStacks.push_back(&argStack);
	rootStacks.push_back(&selfStack);
	rootStacks.push_back(&resultStack);
	rootStacks.push_back(&scopeStack);
}

Machine::~Machine()
{
}

void Machine::walkIn(){
}

void Machine::walkOut(){
}

void Machine::pushResult(object::Handler<object::Object> obj){
	resultStack.push(obj.get());
}
object::Handler<object::Object> Machine::getArgument(){
	return object::Handler<object::Object>(argStack.top());
}
object::Handler<object::Object> Machine::getSelf(){
	return object::Handler<object::Object>(selfStack.top());
}
object::Handler<object::SystemObject> Machine::getTopLevel(){
	return object::Handler<object::Object>(heap.getSystemObject());
}
object::Handler<object::Object> Machine::getLocal()
{
	return object::Handler<object::Object>(scopeStack.top());
}
void Machine::enterLocal(object::Handler<object::Object> local, object::Handler<object::Object> parent)
{
	this->log.t(TAG, 0, "enter local (depth: %d->%d)", scopeStack.size(), scopeStack.size()+1);
	if(parent){
		local->setSlot("$$parent", parent);
	}
	scopeStack.push(local.get());
}
void Machine::endLocal(object::Handler<object::Object> local)
{
	if(scopeStack.top() != local.get()){
		this->log.e(TAG, 0, "[BUG] calling \"end local\" was forgotten!");
	}else if(scopeStack.size() <= 1){
		this->log.e(TAG, 0, "[BUG] leaving from top level scope!!");
	}
	this->log.t(TAG, 0, "leaving local (depth: %d->%d)", scopeStack.size(), scopeStack.size()-1);
	scopeStack.pop();
}

object::Handler<object::Object> Machine::resolveScope(const std::string& name)
{
	if(name.compare("self") == 0){
		this->log.t(TAG, 0, "Scope resolved: self");
		return getSelf();
	}else if(name.compare("local") == 0){
		this->log.t(TAG, 0, "Scope resolved: \"local\"");
		return getLocal();
	}else{
		for(object::Handler<object::Object> obj = getLocal();!obj->isUndefined();obj=obj->getSlot("$$parent")){
			if(obj->has(name)){
				this->log.t(TAG, 0, "Scope resolved: %s in %s", name.c_str(), object::cast<std::string>(obj).c_str());
				return obj;
			}
		}
		this->log.t(TAG, 0, "%s not found.", name.c_str());
		return getLocal();
	}
}

object::Handler<object::Object> Machine::eval(const Node * node, const object::Handler<object::Object>& arg){
	if(arg){
		argStack.push(arg.get());
	}else{
		argStack.push(heap.newUndefinedObject().get());
	}
	node->accept(*this);
	argStack.pop();
	return object::Handler<object::Object>(resultStack.pop());
}
object::Handler<object::Object> Machine::send(const object::Handler<object::Object>& self, const std::string& message, const object::Handler<object::Object>& arg){
	this->log.t(TAG, 0, "Sending %s on %s.",
			message.c_str(),
			object::cast<std::string>(self).c_str()
			);
	if(arg){
		argStack.push(arg.get());
	}else{
		argStack.push(heap.newUndefinedObject().get());
	}
	if(self){
		selfStack.push(self.get());
		self->getSlot(message)->eval(*this);
		selfStack.pop();
	}else{
		self->getSlot(message)->eval(*this);
	}
	argStack.pop();
	return object::Handler<object::Object>(resultStack.pop());
}

void Machine::walkImpl(const BoolLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Walked Boolean node: %s", node.getLiteral() ? "true" : "false");
	pushResult(heap.newBooleanObject(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Walked Numeric node: %f", node.getLiteral());
	pushResult(heap.newNumericObject(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Walked String node: %s", node.getLiteral().c_str());
	pushResult(heap.newStringObject(node.getLiteral()));
}
void Machine::walkImpl(const AssignNode & node)
{
	this->log.t(TAG, &node.location(), "Walking assign node.");
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
	if(invokeNode){
		object::Handler<object::Object> destObj(0);
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			if(node.isLocal()){
				destObj = getLocal();
			}else{
				destObj = resolveScope(invokeNode->getMessageName());
			}
		}
		const object::Handler<object::StringObject> nameObj(heap.newStringObject(invokeNode->getMessageName()));

		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), rhsObj.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked assign node: %s.%s (=>%s)",
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(nameObj).c_str(),
				object::cast<std::string>(rhsObj).c_str()
				);
		pushResult(rhsObj);
	}else if(idxNode){
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), rhsObj.get()));
		this->log.t(TAG, &idxNode->location(), "Walked assign node: %s[%s] (=>%s)",
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(idxObj).c_str(),
				object::cast<std::string>(rhsObj).c_str()
				);
		pushResult(rhsObj);
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
	this->log.t(TAG, &node.location(), "Walked op assign node: %s", node.getOp().c_str());
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
	if(invokeNode){
		object::Handler<object::Object> destObj(0);
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		const object::Handler<object::StringObject> nameObj = heap.newStringObject(invokeNode->getMessageName());

		const object::Handler<object::Object> operandObj = send(destObj, "getSlot", heap.newArrayObject(1, nameObj.get()));
		const object::Handler<object::Object> result = send(operandObj, node.getOp(), heap.newArrayObject(1, rhsObj.get()));

		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), result.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked op(%s %s) assign node %s.%s (%s -> %s)",
				node.getOp().c_str(),
				object::cast<std::string>(rhsObj).c_str(),
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(nameObj).c_str(),
				object::cast<std::string>(operandObj).c_str(),
				object::cast<std::string>(result).c_str()
				);
		pushResult(result);
	}else if(idxNode){
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());

		const object::Handler<object::Object> operandObj = send(destObj, "index", idxObj);
		const object::Handler<object::Object> result = send(operandObj, node.getOp(), heap.newArrayObject(1, rhsObj.get()));

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), result.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked op(%s %s) assign node %s[%s] (%s -> %s)",
				node.getOp().c_str(),
				object::cast<std::string>(rhsObj).c_str(),
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(idxObj).c_str(),
				object::cast<std::string>(operandObj).c_str(),
				object::cast<std::string>(result).c_str()
				);
		pushResult(result);
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid op assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const IndexAcessNode & node)
{
	this->log.t(TAG, &node.location(), "Walking index access node");
	const object::Handler<object::Object> destObj = eval(node.getExprNode());
	this->log.t(TAG, &node.location(), "Walked index access node on %s. (Lazy eval)",
			object::cast<std::string>(destObj).c_str()
			);
	pushResult(send(destObj, "index", heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const BindNode & node)
{
	this->log.t(TAG, &node.location(), "Walked binding node.(Lazy eval)");
	pushResult(eval(node.getExprNode(), heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const PostOpNode & node)
{
	this->log.t(TAG, &node.location(), "Walking post op node.", node.getOp().c_str());
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getExprNode());
	if(invokeNode){
		object::Handler<object::Object> destObj(0);
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		const object::Handler<object::StringObject> nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Handler<object::Object> operandObj = send(destObj, "getSlot", heap.newArrayObject(1, nameObj.get()));
		const object::Handler<object::Object> result = send(operandObj, node.getOp());

		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), result.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked post op(%s) node %s.%s (%s -> %s)",
				node.getOp().c_str(),
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(nameObj).c_str(),
				object::cast<std::string>(operandObj).c_str(),
				object::cast<std::string>(result).c_str()
				);
		pushResult(operandObj);
	}else if(idxNode){
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());

		const object::Handler<object::Object> operandObj = send(destObj, "index", idxObj);
		const object::Handler<object::Object> result = send(operandObj, node.getOp());

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), result.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked post op(%s) assign node %s[%s] (%s -> %s)",
				node.getOp().c_str(),
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(idxObj).c_str(),
				object::cast<std::string>(operandObj).c_str(),
				object::cast<std::string>(result).c_str()
				);
		pushResult(operandObj);
	}else{
		this->log.w(TAG, &node.location(), "Invalid post op node.");
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const PreOpNode & node)
{
	this->log.t(TAG, &node.location(), "Walking pre op node.", node.getOp().c_str());
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getExprNode());
	if(invokeNode){
		object::Handler<object::Object> destObj(0);
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		const object::Handler<object::StringObject> nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Handler<object::Object> operandObj = send(destObj, "getSlot", heap.newArrayObject(1, nameObj.get()));
		const object::Handler<object::Object> result = send(operandObj, node.getOp());
		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), result.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked pre op(%s) node %s.%s (%s -> %s)",
				node.getOp().c_str(),
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(nameObj).c_str(),
				object::cast<std::string>(operandObj).c_str(),
				object::cast<std::string>(result).c_str()
				);
		pushResult(result);
	}else if(idxNode){
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());

		const object::Handler<object::Object> operandObj = send(destObj, "index", idxObj);
		const object::Handler<object::Object> result = send(object::Handler<object::Object>(operandObj), node.getOp()) ;

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), result.get()));
		this->log.t(TAG, &invokeNode->location(), "Walked pre op(%s) assign node %s[%s] (%s -> %s)",
				node.getOp().c_str(),
				object::cast<std::string>(destObj).c_str(),
				object::cast<std::string>(idxObj).c_str(),
				object::cast<std::string>(operandObj).c_str(),
				object::cast<std::string>(result).c_str()
				);
		pushResult(result);
	}else{
		this->log.w(TAG, &node.location(), "Invalid pre op node.");
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const BinOpNode & node)
{
	this->log.t(TAG, &node.location(), "Walking bin op node: %s", node.getOp().c_str());
	const object::Handler<object::Object> leftObj = eval(node.getLeftNode());
	const object::Handler<object::Object> rightObj = eval(node.getRightNode());
	const object::Handler<object::Object> result = send(leftObj, node.getOp(), heap.newArrayObject(1, rightObj.get()));
	this->log.t(TAG, &node.location(), "Walked bin op node: %s %s %s => %s, index node.",
			object::cast<std::string>(leftObj).c_str(),
			node.getOp().c_str(),
			object::cast<std::string>(rightObj).c_str(),
			object::cast<std::string>(result).c_str()
			);
	pushResult( result );
}
void Machine::walkImpl(const ObjectNode & node)
{
	this->log.t(TAG, &node.location(), "Walking object node.");
	const object::Handler<object::Object> obj = heap.newObject();

	const size_t argc = node.size();
	for(size_t i=0;i<argc;++i){
		obj->push(eval(node.index(i)));
	}

	std::vector<std::string> args = node.getSlotNames();
	for(std::vector<std::string>::const_iterator it = args.begin();it!=args.end();++it){
		obj->setSlot(*it, eval(node.getSlot(*it)));
	}
	this->log.t(TAG, &node.location(), "Walked object node: %s",
			object::cast<std::string>(obj).c_str()
		);
	pushResult(obj);
}
void Machine::walkImpl(const InvokeNode & node)
{
	this->log.t(TAG, &node.location(), "Walking invoke node: %s", node.getMessageName().c_str());
	if(node.getExprNode()){
		const object::Handler<object::Object> destObj = eval(node.getExprNode());
		const object::Handler<object::Object> result = send(destObj, node.getMessageName(), getArgument());
		this->log.t(TAG, &node.location(), "Walked invoke node: %s.%s (=> %s)",
				object::cast<std::string>(destObj).c_str(),
				node.getMessageName().c_str(),
				object::cast<std::string>(result).c_str()
			);
		pushResult(result);
	}else{
		const object::Handler<object::Object> destObj = resolveScope(node.getMessageName());
		const object::Handler<object::Object> result = send(destObj, node.getMessageName(), getArgument());
		this->log.t(TAG, &node.location(), "Walked invoke node: %s.%s (=> %s)",
				object::cast<std::string>(destObj).c_str(),
				node.getMessageName().c_str(),
				object::cast<std::string>(result).c_str()
			);
		pushResult(result);
	}
}
void Machine::walkImpl(const ContNode & node)
{
	eval(node.getFirstNode());
	this->log.t(TAG, &node.location(), "Walking continuing node.");
	pushResult(eval(node.getNextNode()));
}

Machine::RootIterator::RootIterator(std::vector<Stack<object::Object*>*>::const_iterator start, std::vector<Stack<object::Object*>*>::const_iterator end)
:pCurrent(start), pEnd(end), current(0), end(0)
{
	nextStack();
}
Machine::RootIterator::~RootIterator()
{

}

void Machine::RootIterator::nextStack()
{
	while(this->current == this->end)
	{
		if(pCurrent == pEnd || ++pCurrent == pEnd)
		{
			break;
		}
		this->current = (*pCurrent)->begin();
		this->end = (*pCurrent)->end();
	}
}
bool Machine::RootIterator::hasNext()
{
	return pCurrent != pEnd;
}
object::Object* Machine::RootIterator::next()
{
	object::Object* obj = *current;
	++current;
	nextStack();
	return obj;
}

object::RootHolder::Iterator* Machine::newIterator()
{
	return new RootIterator(rootStacks.begin(), rootStacks.end());
}

}}
