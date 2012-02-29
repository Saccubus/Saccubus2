/*
 * TopLevel.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include <tr1/memory>
#include <cmath>
#include "Object.h"
#include "Cast.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../system/System.h"
#include "../tree/Node.h"

using namespace std::tr1;

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

DEF_BUILTIN(SystemObject, drawShape)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	shared_ptr<system::Shape> shape = self->system.drawShape(
		opt(arg, "x", 0.0),
		opt(arg, "y", 0.0),
		opt(arg, "z", 0.0),
		opt(arg, "shape", "circle"),
		opt(arg, "width", 0.0),
		opt(arg, "height", 0.0),
		opt(arg, "color", 16777215),
		opt(arg, "visible", true),
		opt(arg, "pos", "naka"),
		opt(arg, "mask", false),
		opt(arg, "commentmask", false),
		opt(arg, "alpha", 0.0),
		opt(arg, "rotation", 0.0),
		opt(arg, "mover", "")
	);
	machine.pushResult(self->getHeap().newShapeObject(shape));

}
DEF_BUILTIN(SystemObject, drawText)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	shared_ptr<system::Chat> chat = self->system.drawText(
			opt(arg, "text", ""),
			opt(arg, "x", 0.0),
			opt(arg, "y", 0.0),
			opt(arg, "z", 0.0),
			opt(arg, "size", 14),
			opt(arg, "pos", "naka"),
			opt(arg, "color", 0),
			opt(arg, "bold", false),
			opt(arg, "visible", true),
			opt(arg, "filter", ""),
			opt(arg, "alpha", 0.0),
			opt(arg, "mover", "")
	);
	machine.pushResult(self->getHeap().newChatObject(chat));
}
DEF_BUILTIN(SystemObject, commentTrigger)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	LazyEvalObject* const lazy = dynamic_cast<LazyEvalObject*>(arg);
	if(lazy && arg->has("timer") && (arg->has(0) || arg->has("then"))){
		self->system.commentTrigger(
			opt(arg, "timer", 0.0),
			arg->has("then") ? lazy->getRawNode()->getSlot("then") : lazy->getRawNode()->index(0)
		);
	}
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, timer)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	LazyEvalObject* const lazy = dynamic_cast<LazyEvalObject*>(arg);
	if(lazy && arg->has("timer") && (arg->has(0) || arg->has("then"))){
		self->system.timer(
			opt(arg, "timer", 0.0),
			arg->has("then") ? lazy->getRawNode()->getSlot("then") : lazy->getRawNode()->index(0)
		);
	}
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, jump)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	self->system.jump(
		(arg->has("id") ? cast<std::string>(arg->getSlot("id")) : opt(arg, 0, "")),
		opt(arg, "msg", ""),
		opt(arg, "from", 0.0),
		opt(arg, "length", 0.0),
		opt(arg, "return", false),
		opt(arg, "returnmsg", ""),
		opt(arg, "newwindow", false)
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, jumpCancel)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	self->system.jumpCancel();
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, seek)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	if(arg->has("vpos")){
		self->system.seek(
			cast<double>(self->getSlot("vpos")),
			opt(arg, "msg", "")
		);
	}
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, addMarker)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	if(arg->has("name") && arg->has("vpos")){
		self->system.addMarker(
			cast<std::string>(self->getSlot("name")),
			cast<double>(self->getSlot("vpos"))
		);
	}
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, getMarker)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	if(arg->has("name")){
		machine.pushResult(self->getHeap().newNumericObject(self->system.getMarker(cast<std::string>(arg->getSlot("name")))));
	}else{
		machine.pushResult(self->getHeap().newUndefinedObject());
	}
}
DEF_BUILTIN(SystemObject, sum)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	shared_ptr<system::Sum> sum = self->system.sum(
		opt(arg, "x", 0),
		opt(arg, "y", 0),
		opt(arg, "size", 30),
		opt(arg, "color", 16777215),
		opt(arg, "visible", true),
		opt(arg, "enabled", true),
		opt(arg, "pos", "naka"),
		opt(arg, "asc", false),
		opt(arg, "unit", "人"),
		opt(arg, "buttononly", false),
		opt(arg, "words", std::vector<std::string>()),
		opt(arg, "partial", false)
	);
	machine.pushResult(self->getHeap().newSumObject(sum));
}
DEF_BUILTIN(SystemObject, showResult)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	shared_ptr<system::SumResult> sumResult = self->system.showResult(
		opt(arg, "x", 0),
		opt(arg, "y", 0),
		opt(arg, "color", 16777215),
		opt(arg, "visible", true),
		opt(arg, "pos", "naka"),
		opt(arg, "unit", "人"),
		opt(arg, "asc", false),
		opt(arg, "sum", std::vector<std::tr1::shared_ptr<system::Sum> >())
	);
	machine.pushResult(self->getHeap().newSumResultObject(sumResult));
}
DEF_BUILTIN(SystemObject, replace)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	std::string src = opt(arg, "src", "");
	shared_ptr<system::Replace> replace = self->system.replace(
		src,
		opt(arg, "dst", src),
		opt(arg, "enabled", true),
		opt(arg, "target", ""),
		opt(arg, "fill", false),
		opt(arg, "partial", true),
		opt(arg, "color", system::Replace::SAME_COLOR), //変更しない
		opt(arg, "size", ""),
		opt(arg, "pos", "")
	);
	machine.pushResult(self->getHeap().newReplaceObject(replace));
}
DEF_BUILTIN(SystemObject, screenWidth)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	system::System& system = self->system;
	machine.pushResult(self->getHeap().newNumericObject(system.screenWidth()));
}
DEF_BUILTIN(SystemObject, screenHeight)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	system::System& system = self->system;
	machine.pushResult(self->getHeap().newNumericObject(system.screenHeight()));
}
DEF_BUILTIN(SystemObject, addButton)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	shared_ptr<system::Button> button = self->system.addButton(
		opt(arg, "message", ""),
		opt(arg, "mail", ""),
		opt(arg, "vpos", 0),
		opt(arg, "commes", ""),
		opt(arg, "commail", ""),
		opt(arg, "comvisible", true),
		opt(arg, "limit", 1),
		opt(arg, "hidden", false)
	);
	machine.pushResult(self->getHeap().newButtonObject(button));
}
DEF_BUILTIN(SystemObject, playStartTime)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	system::System& system = self->system;
	machine.pushResult(self->getHeap().newNumericObject(system.playStartTime()));
}
DEF_BUILTIN(SystemObject, BGM)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	self->system.BGM(
		opt(arg, "id", "sm9"),
		opt(arg, "x", 0.0),
		opt(arg, "y", 0.0),
		opt(arg, "width", 120.0),
		opt(arg, "height", 90.0),
		opt(arg, "visual", false),
		opt(arg, "volume", 50)
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, playBGM)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	self->system.playBGM(cast<int>(machine.getArgument()->index(0)));
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, stopBGM)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	self->system.stopBGM(cast<int>(machine.getArgument()->index(0)));
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, addAtPausePoint)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	self->system.addAtPausePoint(
		opt(arg, "vpos", 0.0), //FIXME: 詳細不明
		opt(arg, "wait", 0.0) //FIXME: 詳細不明
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, addPostRoute)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	self->system.addPostRoute(
		opt(arg, "match", ""),
		opt(arg, "id", "default"), //FIXME: 詳細不明
		opt(arg, "button", "") //FIXME: 詳細不明
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, CM)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	Object* const arg = machine.getArgument();
	self->system.CM(
			opt(arg, "id", ""),
			opt(arg, "time", NAN),
			opt(arg, "pause", false),
			opt(arg, "link", ""),
			opt(arg, "volume", 0.0)
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, playCM)
{
	SystemObject* const self = dynamic_cast<SystemObject*>(machine.getSelf());
	self->system.playCM(cast<int>(machine.getArgument()->index(0)));
	machine.pushResult(self->getHeap().newUndefinedObject());
}

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

