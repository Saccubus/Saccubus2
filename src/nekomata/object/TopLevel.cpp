/*
 * TopLevel.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include "../Nekomata.h"
#include "Object.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../machine/System.h"

namespace nekomata{
namespace object{

TopLevelObject::TopLevelObject(ObjectHeap& heap, machine::System& system)
:HookableObject(heap), system(system)
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
TopLevelObject::~TopLevelObject()
{

}


//---------------------------------------------------------------------------------------------------------------------
DEF_BUILTIN(TopLevelObject, drawShape){}
DEF_BUILTIN(TopLevelObject, drawText){}
DEF_BUILTIN(TopLevelObject, commentTrigger){}
DEF_BUILTIN(TopLevelObject, timer){}
DEF_BUILTIN(TopLevelObject, jump){}
DEF_BUILTIN(TopLevelObject, jumpCancel){}
DEF_BUILTIN(TopLevelObject, seek){}
DEF_BUILTIN(TopLevelObject, addMarker){}
DEF_BUILTIN(TopLevelObject, getMarker){}
DEF_BUILTIN(TopLevelObject, sum){}
DEF_BUILTIN(TopLevelObject, showResult){}
DEF_BUILTIN(TopLevelObject, replace){}
DEF_BUILTIN(TopLevelObject, screenWidth){}
DEF_BUILTIN(TopLevelObject, screenHeight){}
DEF_BUILTIN(TopLevelObject, addButton){}
DEF_BUILTIN(TopLevelObject, playStartTime){}
DEF_BUILTIN(TopLevelObject, BGM){}
DEF_BUILTIN(TopLevelObject, playBGM){}
DEF_BUILTIN(TopLevelObject, stopBGM){}
DEF_BUILTIN(TopLevelObject, addAtPausePoint){}
DEF_BUILTIN(TopLevelObject, addPostRoute){}
DEF_BUILTIN(TopLevelObject, CM){}
DEF_BUILTIN(TopLevelObject, playCM){}

//---------------------------------------------------------------------------------------------------------------------

DEF_HOOK_GETTER(TopLevelObject, commentColor)
{
	return heap.newNumericObject(dynamic_cast<TopLevelObject&>(self).system.commentColor());
}
DEF_HOOK_SETTER(TopLevelObject, commentColor)
{
	dynamic_cast<TopLevelObject&>(self).system.commentColor(static_cast<unsigned int>(obj->index(0)->toNumericObject()->toNumeric()));
}
DEF_HOOK_GETTER(TopLevelObject, commentPlace)
{
	return heap.newStringObject(dynamic_cast<TopLevelObject&>(self).system.commentPlace());
}
DEF_HOOK_SETTER(TopLevelObject, commentPlace)
{
	dynamic_cast<TopLevelObject&>(self).system.commentPlace(obj->index(0)->toStringObject()->toString());
}
DEF_HOOK_GETTER(TopLevelObject, commentSize)
{
	return heap.newStringObject(dynamic_cast<TopLevelObject&>(self).system.commentSize());
}
DEF_HOOK_SETTER(TopLevelObject, commentSize)
{
	dynamic_cast<TopLevelObject&>(self).system.commentSize(obj->index(0)->toStringObject()->toString());
}
DEF_HOOK_GETTER(TopLevelObject, commentInvisible)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.commentInvisible());
}
DEF_HOOK_SETTER(TopLevelObject, commentInvisible)
{
	dynamic_cast<TopLevelObject&>(self).system.commentInvisible(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, commentReverse)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.commentReverse());
}
DEF_HOOK_SETTER(TopLevelObject, commentReverse)
{
	dynamic_cast<TopLevelObject&>(self).system.commentReverse(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, defaultSage)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.defaultSage());
}
DEF_HOOK_SETTER(TopLevelObject, defaultSage)
{
	dynamic_cast<TopLevelObject&>(self).system.defaultSage(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, postDisabled)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.postDisabled());
}
DEF_HOOK_SETTER(TopLevelObject, postDisabled)
{
	dynamic_cast<TopLevelObject&>(self).system.postDisabled(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, seekDisabled)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.seekDisabled());
}
DEF_HOOK_SETTER(TopLevelObject, seekDisabled)
{
	dynamic_cast<TopLevelObject&>(self).system.seekDisabled(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, isLoaded)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.isLoaded());
}
DEF_HOOK_SETTER(TopLevelObject, isLoaded)
{
	dynamic_cast<TopLevelObject&>(self).system.isLoaded(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, isWide)
{
	return heap.newBooleanObject(dynamic_cast<TopLevelObject&>(self).system.isWide());
}
DEF_HOOK_SETTER(TopLevelObject, isWide)
{
	dynamic_cast<TopLevelObject&>(self).system.isWide(obj->index(0)->toBooleanObject()->toBool());
}
DEF_HOOK_GETTER(TopLevelObject, lastVideo)
{
	return heap.newStringObject(dynamic_cast<TopLevelObject&>(self).system.lastVideo());
}
DEF_HOOK_SETTER(TopLevelObject, lastVideo)
{
	dynamic_cast<TopLevelObject&>(self).system.lastVideo(obj->index(0)->toStringObject()->toString());
}

}
}

