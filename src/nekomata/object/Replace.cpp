/*
 * Replace.cpp
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

ReplaceObject::ReplaceObject(Object& parent)
:HookableObject(parent), replace((system::Replace*)0)
{
	ADD_HOOK_ACCESSOR(src);
	ADD_HOOK_ACCESSOR(dst);
	ADD_HOOK_ACCESSOR(enabled);
	ADD_HOOK_ACCESSOR(target);
	ADD_HOOK_ACCESSOR(fill);
	ADD_HOOK_ACCESSOR(partial);
	ADD_HOOK_ACCESSOR(color);
	ADD_HOOK_ACCESSOR(size);
	ADD_HOOK_ACCESSOR(pos);
}
DEF_HOOK_ACCESSOR_STR(ReplaceObject, src, replace);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, dst, replace);
DEF_HOOK_ACCESSOR_BOOL(ReplaceObject, enabled, replace);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, target, replace);
DEF_HOOK_ACCESSOR_BOOL(ReplaceObject, fill, replace);
DEF_HOOK_ACCESSOR_BOOL(ReplaceObject, partial, replace);
DEF_HOOK_ACCESSOR_INT(ReplaceObject, color, replace, unsigned int);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, size, replace);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, pos, replace);

ReplaceObject::ReplaceObject(ReplaceObject& parent, int hash, std::tr1::shared_ptr<system::Replace> replace)
:HookableObject(parent, hash), replace(replace)
{

}
ReplaceObject::~ReplaceObject()
{

}


}
}
