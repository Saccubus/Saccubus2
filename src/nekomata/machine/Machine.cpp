/*
 * Machine::.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Machine.h"

#include "../tree/NodeWalker.h"
#include "../object/Object.h"
#include "../object/Cast.h"
#include "../object/Heap.h"
#include "../tree/Node.h"
#include <tr1/memory>
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
object::Handler<object::Object> Machine::getTopLevel(){
	return object::Handler<object::Object>(selfStack.bottom());
}
object::Handler<object::Object> Machine::getLocal()
{
	return object::Handler<object::Object>(scopeStack.top());
}
void Machine::enterLocal(object::Handler<object::Object> local, object::Handler<object::Object> parent)
{
	this->log.t(TAG, 0, "enter new local (now depth: %d)", scopeStack.size());
	if(parent){
		local->setSlot("$$parent", parent);
	}
	scopeStack.push(local.get());
}
void Machine::endLocal(object::Handler<object::Object> local)
{
	if(scopeStack.top() != local.get()){
		this->log.e(TAG, 0, "[BUG] calling \"end local\" was forgotten!");
	}
	scopeStack.pop();
}

object::Handler<object::Object> Machine::resolveScope(const std::string& name)
{
	if(name.compare("self") == 0){
		this->log.t(TAG, 0, "Scope Resolved: self");
		return getSelf();
	}else if(name.compare("local") == 0){
		this->log.t(TAG, 0, "Scope Resolved: \"local\"");
		return getLocal();
	}else{
		for(object::Handler<object::Object> obj = getLocal();!obj->isUndefined();obj=obj->getSlot("$$parent")){
			const object::Handler<object::Object> slot = obj->getSlot(name);
			if(!slot->isUndefined()){
				this->log.t(TAG, 0, "Scope Resolved: %s in %s", name.c_str(), object::cast<std::string>(obj).c_str());
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
	this->log.t(TAG, &node.location(), "Evaluating Boolean node: %s", node.getLiteral() ? "true" : "false");
	pushResult(heap.newBooleanObject(node.getLiteral()));
}
void Machine::walkImpl(const NumericLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating Numeric node: %f", node.getLiteral());
	pushResult(heap.newNumericObject(node.getLiteral()));
}
void Machine::walkImpl(const StringLiteralNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating Numeric node: %s", node.getLiteral().c_str());
	pushResult(heap.newStringObject(node.getLiteral()));
}
void Machine::walkImpl(const AssignNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating assign node");
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
	if(invokeNode){
		this->log.t(TAG, &invokeNode->location(), "Evaluating assign node with invoke node.");
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
		pushResult(rhsObj);
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating assign node with index access node.");
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), rhsObj.get()));
		pushResult(rhsObj);
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const OpAssignNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating op assign node: %s", node.getOp().c_str());
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getLeftNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getLeftNode());
	if(invokeNode){
		this->log.t(TAG, &invokeNode->location(), "Evaluating op assign node with invoke node.");
		object::Handler<object::Object> destObj(0);
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		object::Handler<object::StringObject> const nameObj = heap.newStringObject(invokeNode->getMessageName());

		const object::Handler<object::Object> operandObj = send(destObj, "getSlot", heap.newArrayObject(1, nameObj.get()));
		const object::Handler<object::Object> result = send(operandObj, node.getOp(), heap.newArrayObject(1, rhsObj.get()));

		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), result.get()));
		pushResult(result);
	}else if(idxNode){
		this->log.t(TAG, &idxNode->location(), "Evaluating op assign node with index access node.");
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());
		const object::Handler<object::Object> rhsObj = eval(node.getRightNode());

		const object::Handler<object::Object> operandObj = send(destObj, "index", idxObj);
		const object::Handler<object::Object> result = send(operandObj, node.getOp(), heap.newArrayObject(1, rhsObj.get()));

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), result.get()));
		pushResult(result);
	}else{
		this->log.w(TAG, &node.getLeftNode()->location(), "Invalid op assign node.");
		pushResult(heap.newUndefinedObject());
	}
}
void Machine::walkImpl(const IndexAcessNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating index access node.");
	const object::Handler<object::Object> destObj = eval(node.getExprNode());
	pushResult(send(destObj, "index", heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const BindNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating bind node.");
	pushResult(eval(node.getExprNode(), heap.newLazyEvalObject(*this, node.getObjectNode())));
}
void Machine::walkImpl(const PostOpNode & node)
{
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getExprNode());
	if(invokeNode){
		this->log.t(TAG, &node.location(), "Evaluating post op node with invoke node: %s", node.getOp().c_str());
		object::Handler<object::Object> destObj(0);
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		object::Handler<object::StringObject> const nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Handler<object::Object> operandObj = send(destObj, "getSlot", heap.newArrayObject(1, nameObj.get()));
		const object::Handler<object::Object> result( send(operandObj, node.getOp()) );

		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), result.get()));
		pushResult(operandObj);
	}else if(idxNode){
		this->log.t(TAG, &node.location(), "Evaluating post op node with index access node: %s", node.getOp().c_str());
		const object::Handler<object::Object> destObj(eval(idxNode->getExprNode()));
		const object::Handler<object::Object> idxObj(eval(idxNode->getObjectNode()));

		const object::Handler<object::Object> operandObj(send(destObj, "index", idxObj));
		const object::Handler<object::Object> result( send(operandObj, node.getOp()) );

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), result.get()));

		pushResult(operandObj);
	}else{
		this->log.w(TAG, &node.location(), "Invalid post op node.");
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const PreOpNode & node)
{
	const InvokeNode* const invokeNode = dynamic_cast<const InvokeNode*>(node.getExprNode());
	const IndexAcessNode* const idxNode = dynamic_cast<const IndexAcessNode*>(node.getExprNode());
	if(invokeNode){
		this->log.t(TAG, &node.location(), "Evaluating pre op node with invoke node: %s", node.getOp().c_str());
		object::Handler<object::Object> destObj(0);
		if(invokeNode->getExprNode()){
			destObj = eval(invokeNode->getExprNode());
		}else{
			destObj = resolveScope(invokeNode->getMessageName());
		}
		object::Handler<object::StringObject> const nameObj = heap.newStringObject(invokeNode->getMessageName());

		object::Handler<object::Object> operandObj = send(destObj, "getSlot", heap.newArrayObject(1, nameObj.get()));
		const object::Handler<object::Object> result( send(operandObj, node.getOp()) );
		send(destObj, "setSlot", heap.newArrayObject(2, nameObj.get(), result.get()));

		pushResult(result);
	}else if(idxNode){
		this->log.t(TAG, &node.location(), "Evaluating pre op node with index access node: %s", node.getOp().c_str());
		const object::Handler<object::Object> destObj = eval(idxNode->getExprNode());
		const object::Handler<object::Object> idxObj = eval(idxNode->getObjectNode());

		const object::Handler<object::Object> operandObj = send(destObj, "index", idxObj);
		const object::Handler<object::Object> result( send(object::Handler<object::Object>(operandObj), node.getOp()) );

		send(destObj, "indexSet", heap.newArrayObject(2, idxObj->index(0).get(), result.get()));

		pushResult(operandObj);
	}else{
		this->log.w(TAG, &node.location(), "Invalid pre op node.");
		pushResult(eval(node.getExprNode()));
	}
}
void Machine::walkImpl(const BinOpNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating bin op node: %s", node.getOp().c_str());
	const object::Handler<object::Object> leftObj = eval(node.getLeftNode());
	const object::Handler<object::Object> rightObj = eval(node.getRightNode());
	pushResult( send(leftObj, node.getOp(), heap.newArrayObject(1, rightObj.get())) );
}
void Machine::walkImpl(const ObjectNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating object node.");
	const object::Handler<object::Object> obj = heap.newObject();

	const size_t argc = node.size();
	for(size_t i=0;i<argc;++i){
		obj->push(eval(node.index(i)));
	}

	std::vector<std::string> args = node.getSlotNames();
	for(std::vector<std::string>::const_iterator it = args.begin();it!=args.end();++it){
		obj->setSlot(*it, eval(node.getSlot(*it)));
	}
	pushResult(obj);
}
void Machine::walkImpl(const InvokeNode & node)
{
	this->log.t(TAG, &node.location(), "Evaluating invoke node.");
	if(node.getExprNode()){
		const object::Handler<object::Object> destObj = eval(node.getExprNode());
		pushResult(send(destObj, node.getMessageName(), getArgument()));
	}else{
		pushResult(send(resolveScope(node.getMessageName()), node.getMessageName(), getArgument()));
	}
}
void Machine::walkImpl(const ContNode & node)
{
	eval(node.getFirstNode());
	this->log.t(TAG, &node.location(), "Evaluating continuing node.");
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
