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

ChatObject::ChatObject(Object& parent)
:HookableObject(parent), chat((system::Chat*)0)
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
DEF_HOOK_ACCESSOR_STR(ChatObject, text, chat);
DEF_HOOK_ACCESSOR_DOUBLE(ChatObject, x, chat);
DEF_HOOK_ACCESSOR_DOUBLE(ChatObject, y, chat);
DEF_HOOK_ACCESSOR_DOUBLE(ChatObject, z, chat);
DEF_HOOK_ACCESSOR_DOUBLE(ChatObject, size, chat);
DEF_HOOK_ACCESSOR_STR(ChatObject, pos, chat);
DEF_HOOK_ACCESSOR_INT(ChatObject, color, chat, unsigned int);
DEF_HOOK_ACCESSOR_BOOL(ChatObject, bold, chat);
DEF_HOOK_ACCESSOR_BOOL(ChatObject, visible, chat);
DEF_HOOK_ACCESSOR_STR(ChatObject, filter, chat);
DEF_HOOK_ACCESSOR_DOUBLE(ChatObject, alpha, chat);
DEF_HOOK_ACCESSOR_STR(ChatObject, mover, chat);

ChatObject::ChatObject(ChatObject& parent, int hash, std::tr1::shared_ptr<system::Chat> chat)
:HookableObject(parent, hash), chat(chat)
{

}
ChatObject::~ChatObject()
{

}


}
}
