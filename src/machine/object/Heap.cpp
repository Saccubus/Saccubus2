/*
 * Heap.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"
namespace machine{

ObjectHeap::ObjectHeap()
:trueObject(this, 0, true)
,falseObject(this, 0, false)
,undefinedObject(this, 0)
{

}
ObjectHeap::~ObjectHeap()
{

}

Object* ObjectHeap::newObject(const Object *parent)
{
	return 0;
}



Object* ObjectHeap::newObject(const tree::ObjectNode *objNode)
{
	return 0;
}



StringObject* ObjectHeap::newStringObject(const std::string & str)
{
	return 0;
}



BooleanObject* ObjectHeap::newBooleanObject(const bool val)
{
	if(val){
		return &trueObject;
	}else{
		return &falseObject;
	}
}



NumericObject* ObjectHeap::newNumericObject(const double num)
{
	return 0;
}

UndefinedObject* ObjectHeap::newUndefinedObject()
{
	return &undefinedObject;
}



NodeObject* ObjectHeap::newNodeObject(tree::Node *node)
{
	return 0;
}



void machine::ObjectHeap::gc(const Object *global)
{
}
}

