/*
 * Shape.cpp
 *
 *  Created on: 2012/02/27
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../system/System.h"

namespace nekomata{
namespace object{

ShapeObject::ShapeObject(Object& parent)
:HookableObject(parent), shape((system::Shape*)0)
{
	ADD_HOOK_ACCESSOR(x);
	ADD_HOOK_ACCESSOR(y);
	ADD_HOOK_ACCESSOR(z);
	ADD_HOOK_ACCESSOR(shape);
	ADD_HOOK_ACCESSOR(width);
	ADD_HOOK_ACCESSOR(height);
	ADD_HOOK_ACCESSOR(color);
	ADD_HOOK_ACCESSOR(visible);
	ADD_HOOK_ACCESSOR(pos);
	ADD_HOOK_ACCESSOR(mask);
	ADD_HOOK_ACCESSOR(commentmask);
	ADD_HOOK_ACCESSOR(alpha);
	ADD_HOOK_ACCESSOR(rotation);
	ADD_HOOK_ACCESSOR(mover);
}
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, x, shape);
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, y, shape);
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, z, shape);
DEF_HOOK_ACCESSOR_STR(ShapeObject, shape, shape);
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, width, shape);
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, height, shape);
DEF_HOOK_ACCESSOR_INT(ShapeObject, color, shape, unsigned int);
DEF_HOOK_ACCESSOR_BOOL(ShapeObject, visible, shape);
DEF_HOOK_ACCESSOR_STR(ShapeObject, pos, shape);
DEF_HOOK_ACCESSOR_BOOL(ShapeObject, mask, shape);
DEF_HOOK_ACCESSOR_BOOL(ShapeObject, commentmask, shape);
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, alpha, shape);
DEF_HOOK_ACCESSOR_DOUBLE(ShapeObject, rotation, shape);
DEF_HOOK_ACCESSOR_STR(ShapeObject, mover, shape);

ShapeObject::ShapeObject(ShapeObject& parent, int hash, std::tr1::shared_ptr<system::Shape> shape)
:HookableObject(parent, hash), shape(shape)
{

}
ShapeObject::~ShapeObject()
{

}


}}
