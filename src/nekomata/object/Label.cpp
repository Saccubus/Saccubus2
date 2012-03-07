/*
 * Chat.cpp
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

LabelObject::LabelObject(Object& parent)
:HookableObject(parent), label((system::Label*)0)
{
	ADD_HOOK_ACCESSOR(text);
	ADD_HOOK_ACCESSOR(x);
	ADD_HOOK_ACCESSOR(y);
	ADD_HOOK_ACCESSOR(z);
	ADD_HOOK_ACCESSOR(size);
	ADD_HOOK_ACCESSOR(pos);
	ADD_HOOK_ACCESSOR(color);
	ADD_HOOK_ACCESSOR(bold);
	ADD_HOOK_ACCESSOR(visible);
	ADD_HOOK_ACCESSOR(filter);
	ADD_HOOK_ACCESSOR(alpha);
	ADD_HOOK_ACCESSOR(mover);
}
DEF_HOOK_ACCESSOR_STR(LabelObject, text, label);
DEF_HOOK_ACCESSOR_DOUBLE(LabelObject, x, label);
DEF_HOOK_ACCESSOR_DOUBLE(LabelObject, y, label);
DEF_HOOK_ACCESSOR_DOUBLE(LabelObject, z, label);
DEF_HOOK_ACCESSOR_DOUBLE(LabelObject, size, label);
DEF_HOOK_ACCESSOR_STR(LabelObject, pos, label);
DEF_HOOK_ACCESSOR_INT(LabelObject, color, label, unsigned int);
DEF_HOOK_ACCESSOR_BOOL(LabelObject, bold, label);
DEF_HOOK_ACCESSOR_BOOL(LabelObject, visible, label);
DEF_HOOK_ACCESSOR_STR(LabelObject, filter, label);
DEF_HOOK_ACCESSOR_DOUBLE(LabelObject, alpha, label);
DEF_HOOK_ACCESSOR_STR(LabelObject, mover, label);

LabelObject::LabelObject(LabelObject& parent, int hash, std::tr1::shared_ptr<system::Label> label)
:HookableObject(parent, hash), label(label)
{

}
LabelObject::~LabelObject()
{

}


}}
