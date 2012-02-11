/*
 * Object.cpp
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#include "Object.h"

namespace machine
{

Object::Object(ObjectHeap* const heap)
:parentHeap(parentHeap)
{
	// TODO Auto-generated constructor stub

}

Object::~Object()
{
	// TODO Auto-generated destructor stub
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
	return 0;
}



NumericObject* ObjectHeap::newNumericObject(const double num)
{
	return 0;
}



NodeObject* ObjectHeap::newNodeObject(tree::Node *node)
{
	return 0;
}



void machine::ObjectHeap::gc(const Object *global)
{
}

}
 /* namespace machine */
