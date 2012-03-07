/*
 * Button.cpp
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

ButtonObject::ButtonObject(Object& parent)
:HookableObject(parent), button((system::Button*)0)
{
	ADD_HOOK_ACCESSOR(message);
	ADD_HOOK_ACCESSOR(mail);
	ADD_HOOK_ACCESSOR(vpos);
	ADD_HOOK_ACCESSOR(commes);
	ADD_HOOK_ACCESSOR(commail);
	ADD_HOOK_ACCESSOR(comvisible);
	ADD_HOOK_ACCESSOR(limit);
	ADD_HOOK_ACCESSOR(hidden);
}
DEF_HOOK_ACCESSOR_STR(ButtonObject, message, button);
DEF_HOOK_ACCESSOR_STR(ButtonObject, mail, button);
DEF_HOOK_ACCESSOR_DOUBLE(ButtonObject, vpos, button);
DEF_HOOK_ACCESSOR_STR(ButtonObject, commes, button);
DEF_HOOK_ACCESSOR_STR(ButtonObject, commail, button);
DEF_HOOK_ACCESSOR_BOOL(ButtonObject, comvisible, button);
DEF_HOOK_ACCESSOR_INT(ButtonObject, limit, button, int);
DEF_HOOK_ACCESSOR_BOOL(ButtonObject, hidden, button);

ButtonObject::ButtonObject(ButtonObject& parent, int hash, std::tr1::shared_ptr<system::Button> button)
:HookableObject(parent, hash), button(button)
{

}
ButtonObject::~ButtonObject()
{

}


}}
