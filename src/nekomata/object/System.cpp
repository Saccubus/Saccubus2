/*
 * TopLevel.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../system/System.h"

namespace nekomata{
namespace object{

SystemObject::SystemObject(Object& parent, system::System& system)
:HookableObject(parent), system(system)
{
	ADD_HOOK_ACCESSOR(commentColor);
	ADD_HOOK_ACCESSOR(commentPlace);
	ADD_HOOK_ACCESSOR(commentSize);
	ADD_HOOK_ACCESSOR(commentInvisible);
	ADD_HOOK_ACCESSOR(commentReverse);
	ADD_HOOK_ACCESSOR(defaultSage);
	ADD_HOOK_ACCESSOR(postDisabled);
	ADD_HOOK_ACCESSOR(seekDisabled);
	ADD_HOOK_ACCESSOR(isLoaded);
	ADD_HOOK_ACCESSOR(isWide);
	ADD_HOOK_ACCESSOR(lastVideo);

	ADD_BUILTIN(drawShape);
	ADD_BUILTIN(drawText);
	ADD_BUILTIN_ALT(drawText, "dt");
	ADD_BUILTIN(commentTrigger);
	ADD_BUILTIN_ALT(commentTrigger, "ctrig");
	ADD_BUILTIN(timer);
	ADD_BUILTIN(jump);
	ADD_BUILTIN(jumpCancel);
	ADD_BUILTIN(seek);
	ADD_BUILTIN(addMarker);
	ADD_BUILTIN(getMarker);
	ADD_BUILTIN(sum);
	ADD_BUILTIN(showResult);
	ADD_BUILTIN(replace);
	ADD_BUILTIN(screenWidth);
	ADD_BUILTIN(screenHeight);
	ADD_BUILTIN(addButton);
	ADD_BUILTIN(playStartTime);
	ADD_BUILTIN(BGM);
	ADD_BUILTIN(playBGM);
	ADD_BUILTIN(stopBGM);
	ADD_BUILTIN(addAtPausePoint);
	ADD_BUILTIN(addPostRoute);
	ADD_BUILTIN(CM);
	ADD_BUILTIN(playCM);
	includeBuitin();
}
SystemObject::~SystemObject()
{

}


//---------------------------------------------------------------------------------------------------------------------
DEF_BUILTIN(SystemObject, drawShape){}
DEF_BUILTIN(SystemObject, drawText){}
DEF_BUILTIN(SystemObject, commentTrigger){}
DEF_BUILTIN(SystemObject, timer){}
DEF_BUILTIN(SystemObject, jump){}
DEF_BUILTIN(SystemObject, jumpCancel){}
DEF_BUILTIN(SystemObject, seek){}
DEF_BUILTIN(SystemObject, addMarker){}
DEF_BUILTIN(SystemObject, getMarker){}
DEF_BUILTIN(SystemObject, sum){}
DEF_BUILTIN(SystemObject, showResult){}
DEF_BUILTIN(SystemObject, replace){}
DEF_BUILTIN(SystemObject, screenWidth){}
DEF_BUILTIN(SystemObject, screenHeight){}
DEF_BUILTIN(SystemObject, addButton){}
DEF_BUILTIN(SystemObject, playStartTime){}
DEF_BUILTIN(SystemObject, BGM){}
DEF_BUILTIN(SystemObject, playBGM){}
DEF_BUILTIN(SystemObject, stopBGM){}
DEF_BUILTIN(SystemObject, addAtPausePoint){}
DEF_BUILTIN(SystemObject, addPostRoute){}
DEF_BUILTIN(SystemObject, CM){}
DEF_BUILTIN(SystemObject, playCM){}

//---------------------------------------------------------------------------------------------------------------------

DEF_HOOK_GETTER(SystemObject, commentColor)
{
	return heap.newNumericObject(dynamic_cast<SystemObject&>(self).system.commentColor());
}
DEF_HOOK_SETTER(SystemObject, commentColor)
{
	dynamic_cast<SystemObject&>(self).system.commentColor(static_cast<unsigned int>(obj->index(0)->toNumericObject()->toNumeric()));
}
DEF_HOOK_GETTER(SystemObject, commentPlace)
{
	return heap.newStringObject(dynamic_cast<SystemObject&>(self).system.commentPlace());
}
DEF_HOOK_SETTER(SystemObject, commentPlace)
{
	dynamic_cast<SystemObject&>(self).system.commentPlace(obj->index(0)->toStringObject()->toString());
}
DEF_HOOK_GETTER(SystemObject, commentSize)
{
	return heap.newStringObject(dynamic_cast<SystemObject&>(self).system.commentSize());
}
DEF_HOOK_SETTER(SystemObject, commentSize)
{
	dynamic_cast<SystemObject&>(self).system.commentSize(obj->index(0)->toStringObject()->toString());
}
DEF_HOOK_GETTER(SystemObject, commentInvisible)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.commentInvisible());
}
DEF_HOOK_SETTER(SystemObject, commentInvisible)
{
	dynamic_cast<SystemObject&>(self).system.commentInvisible(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, commentReverse)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.commentReverse());
}
DEF_HOOK_SETTER(SystemObject, commentReverse)
{
	dynamic_cast<SystemObject&>(self).system.commentReverse(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, defaultSage)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.defaultSage());
}
DEF_HOOK_SETTER(SystemObject, defaultSage)
{
	dynamic_cast<SystemObject&>(self).system.defaultSage(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, postDisabled)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.postDisabled());
}
DEF_HOOK_SETTER(SystemObject, postDisabled)
{
	dynamic_cast<SystemObject&>(self).system.postDisabled(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, seekDisabled)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.seekDisabled());
}
DEF_HOOK_SETTER(SystemObject, seekDisabled)
{
	dynamic_cast<SystemObject&>(self).system.seekDisabled(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, isLoaded)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.isLoaded());
}
DEF_HOOK_SETTER(SystemObject, isLoaded)
{
	dynamic_cast<SystemObject&>(self).system.isLoaded(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, isWide)
{
	return heap.newBooleanObject(dynamic_cast<SystemObject&>(self).system.isWide());
}
DEF_HOOK_SETTER(SystemObject, isWide)
{
	dynamic_cast<SystemObject&>(self).system.isWide(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(SystemObject, lastVideo)
{
	return heap.newStringObject(dynamic_cast<SystemObject&>(self).system.lastVideo());
}
DEF_HOOK_SETTER(SystemObject, lastVideo)
{
	dynamic_cast<SystemObject&>(self).system.lastVideo(obj->index(0)->toStringObject()->toString());
}

}
}

