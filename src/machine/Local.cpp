/*
 * Local.cpp
 *
 *  Created on: 2012/02/16
 *      Author: psi
 */
#include "Machine.h"
#include <math.h>

namespace machine{

LocalObject::LocalObject(ObjectHeap & heap, const unsigned int hash, Stack<Object*> & localStack)
:Object(heap, hash), localStack(localStack)
{
}
LocalObject::~LocalObject()
{
}
void LocalObject::inject(Object *to)
{
}
int LocalObject::push(Object *const item)
{
	return 0;
}
Object *LocalObject::index(size_t idx)
{
	return getHeap().newUndefinedObject();
}
Object *LocalObject::setSlot(const std::string & name, Object *const item)
{
	return item;
}
Object *LocalObject::getSlot(const std::string & name)
{
	bool recursive = true;
	if(name.compare(0, 1, "$") == 0){
		recursive = false;
	}
	for(Stack<Object*>::ReverseIterator it = localStack.rbegin(); it != localStack.rend(); ++it){
		if((*it) != 0){
			Object* const obj = *it;
			Object* resolved = obj->getSlot(name);
			if(!resolved->isUndefined() || !recursive){
				return resolved;
			}
		}else if(!recursive){
			return getHeap().newUndefinedObject();
		}
	}
	return getHeap().newUndefinedObject();
}
bool LocalObject::isUndefined()
{
	return false;
}
void LocalObject::eval(Machine & machine)
{
}
StringObject *LocalObject::toStringObject()
{
	return getHeap().newStringObject("LOCAL OBJECT");
}
NumericObject *LocalObject::toNumericObject()
{
	return getHeap().newNumericObject(NAN);
}
BooleanObject *LocalObject::toBooleanObject()
{
	return getHeap().newBooleanObject(false);
}

}
