/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <tr1/memory>
#include <cmath>
#include <cfloat>
#include <nekomata/logging/Exception.h>
#include "Object.h"
#include "Cast.h"
#include "Heap.h"
#include "../machine/Machine.h"
#include "../tree/Node.h"
#include "../util/StringUtil.h"


using namespace std::tr1;

namespace nekomata{
namespace object{

SystemObject::SystemObject(Object& parent, system::System& system)
:HookableObject(parent), system(system)
{
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
	}
	{
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
	{
		this->setSlot("Object", getHeap().newObject());
	}

}
SystemObject::~SystemObject()
{

}

void SystemObject::setChat(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
{
	ObjectHeap& heap = this->getHeap();
	const Handler<Object> chat(heap.newRawObject());
	chat->setSlot("message", heap.newStringObject(message));
	chat->setSlot("vpos", heap.newNumericObject(vpos));
	chat->setSlot("isYourPost", heap.newBooleanObject(isYourPost));
	chat->setSlot("mail", heap.newStringObject(mail));
	chat->setSlot("fromButton", heap.newBooleanObject(fromButton));
	chat->setSlot("isPremium", heap.newBooleanObject(isPremium));
	chat->setSlot("color", heap.newNumericObject(color));
	chat->setSlot("size", heap.newNumericObject(size));
	chat->setSlot("no", heap.newNumericObject(no));
	chat->freeze();
	this->setSlot("chat", chat);
}


//---------------------------------------------------------------------------------------------------------------------

DEF_BUILTIN(SystemObject, drawShape)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	util::Handler<system::Shape> shape = self->system.drawShape(
		opt(arg, "x", 0.0),
		opt(arg, "y", 0.0),
		opt(arg, "z", 0.0),
		opt(arg, "shape", "circle"),
		opt(arg, "width", 0.0),
		opt(arg, "height", 0.0),
		opt<unsigned int>(arg, "color", 16777215),
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
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	util::Handler<system::Label> label = self->system.drawText(
			arg->has("text") ? cast<std::string>(arg->getSlot("text")) : opt(arg, (size_t)0, ""),
			opt(arg, "x", 0.0),
			opt(arg, "y", 0.0),
			opt(arg, "z", 0.0),
			opt(arg, "size", 14.0),
			opt(arg, "pos", "naka"),
			opt<unsigned int>(arg, "color", 0),
			opt(arg, "bold", false),
			opt(arg, "visible", true),
			opt(arg, "filter", ""),
			opt(arg, "alpha", 0.0),
			opt(arg, "mover", "")
	);
	machine.pushResult(self->getHeap().newLabelObject(label));
}
DEF_BUILTIN(SystemObject, commentTrigger)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	const Handler<LazyEvalObject> lazy(arg);
	if(lazy && (arg->has(0) || arg->has("then"))){
		self->system.commentTrigger(
			opt(arg, "timer", DBL_MAX),
			arg->has("then") ? lazy->getRawNode()->getSlot("then") : lazy->getRawNode()->index(0)
		);
	}
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, timer)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	const Handler<LazyEvalObject> lazy(arg);
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
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	self->system.jump(
		(arg->has("id") ? cast<std::string>(arg->getSlot("id")) : opt(arg, (size_t)0, "")),
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
	const Handler<SystemObject> self(machine.getSelf());
	self->system.jumpCancel();
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, seek)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
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
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
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
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	if(arg->has("name")){
		machine.pushResult(self->getHeap().newNumericObject(self->system.getMarker(cast<std::string>(arg->getSlot("name")))));
	}else{
		machine.pushResult(self->getHeap().newUndefinedObject());
	}
}
DEF_BUILTIN(SystemObject, sum)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	util::Handler<system::Sum> sum = self->system.sum(
		opt(arg, "x", 0.0),
		opt(arg, "y", 0.0),
		opt(arg, "size", 30),
		opt<unsigned int>(arg, "color", 16777215),
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
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	util::Handler<system::SumResult> sumResult = self->system.showResult(
		opt(arg, "x", 0.0),
		opt(arg, "y", 0.0),
		opt<unsigned int>(arg, "color", 16777215),
		opt(arg, "visible", true),
		opt(arg, "pos", "naka"),
		opt(arg, "unit", "人"),
		opt(arg, "asc", false),
		opt(arg, "sum", std::vector<Handler<system::Sum> >())
	);
	machine.pushResult(self->getHeap().newSumResultObject(sumResult));
}
DEF_BUILTIN(SystemObject, replace)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	std::string src = opt(arg, "src", "");
	util::Handler<system::Replace> replace = self->system.replace(
		src,
		opt(arg, "dst", src),
		opt(arg, "enabled", true),
		opt(arg, "target", ""),
		opt(arg, "fill", false),
		opt(arg, "partial", true),
		opt<unsigned int>(arg, "color", system::Replace::SAME_COLOR), //変更しない
		opt(arg, "size", ""),
		opt(arg, "pos", "")
	);
	machine.pushResult(self->getHeap().newReplaceObject(replace));
}
DEF_BUILTIN(SystemObject, screenWidth)
{
	const Handler<SystemObject> self(machine.getSelf());
	system::System& system = self->system;
	machine.pushResult(self->getHeap().newNumericObject(system.screenWidth()));
}
DEF_BUILTIN(SystemObject, screenHeight)
{
	const Handler<SystemObject> self(machine.getSelf());
	system::System& system = self->system;
	machine.pushResult(self->getHeap().newNumericObject(system.screenHeight()));
}
DEF_BUILTIN(SystemObject, addButton)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	util::Handler<system::Button> button = self->system.addButton(
		opt(arg, "message", ""),
		opt(arg, "mail", ""),
		opt(arg, "vpos", 0.0),
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
	const Handler<SystemObject> self(machine.getSelf());
	system::System& system = self->system;
	machine.pushResult(self->getHeap().newNumericObject(system.playStartTime()));
}
DEF_BUILTIN(SystemObject, BGM)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
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
	const Handler<SystemObject> self(machine.getSelf());
	self->system.playBGM(cast<int>(machine.getArgument()->index(0)));
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, stopBGM)
{
	const Handler<SystemObject> self(machine.getSelf());
	self->system.stopBGM(cast<int>(machine.getArgument()->index(0)));
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, addAtPausePoint)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	self->system.addAtPausePoint(
		opt(arg, "vpos", 0.0), //FIXME: 詳細不明
		opt(arg, "wait", 0.0) //FIXME: 詳細不明
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, addPostRoute)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
	self->system.addPostRoute(
		opt(arg, "match", ""),
		opt(arg, "id", "default"), //FIXME: 詳細不明
		opt(arg, "button", "") //FIXME: 詳細不明
	);
	machine.pushResult(self->getHeap().newUndefinedObject());
}
DEF_BUILTIN(SystemObject, CM)
{
	const Handler<SystemObject> self(machine.getSelf());
	const Handler<Object> arg(machine.getArgument());
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
	const Handler<SystemObject> self(machine.getSelf());
	self->system.playCM(cast<int>(machine.getArgument()->index(0)));
	machine.pushResult(self->getHeap().newUndefinedObject());
}

std::string SystemObject::toString()
{
	return util::format("<<SystemObject>>");
}

//---------------------------------------------------------------------------------------------------------------------

DEF_HOOK_GETTER(SystemObject, commentColor)
{
	return heap.newNumericObject(Handler<SystemObject>(self)->system.commentColor());
}
DEF_HOOK_SETTER(SystemObject, commentColor)
{
	Handler<SystemObject>(self)->system.commentColor(cast<unsigned int>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, commentPlace)
{
	return heap.newStringObject(Handler<SystemObject>(self)->system.commentPlace());
}
DEF_HOOK_SETTER(SystemObject, commentPlace)
{
	Handler<SystemObject>(self)->system.commentPlace(cast<std::string>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, commentSize)
{
	return heap.newStringObject(Handler<SystemObject>(self)->system.commentSize());
}
DEF_HOOK_SETTER(SystemObject, commentSize)
{
	Handler<SystemObject>(self)->system.commentSize(cast<std::string>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, commentInvisible)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.commentInvisible());
}
DEF_HOOK_SETTER(SystemObject, commentInvisible)
{
	Handler<SystemObject>(self)->system.commentInvisible(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, commentReverse)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.commentReverse());
}
DEF_HOOK_SETTER(SystemObject, commentReverse)
{
	Handler<SystemObject>(self)->system.commentReverse(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, defaultSage)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.defaultSage());
}
DEF_HOOK_SETTER(SystemObject, defaultSage)
{
	Handler<SystemObject>(self)->system.defaultSage(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, postDisabled)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.postDisabled());
}
DEF_HOOK_SETTER(SystemObject, postDisabled)
{
	Handler<SystemObject>(self)->system.postDisabled(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, seekDisabled)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.seekDisabled());
}
DEF_HOOK_SETTER(SystemObject, seekDisabled)
{
	Handler<SystemObject>(self)->system.seekDisabled(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, isLoaded)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.isLoaded());
}
DEF_HOOK_SETTER(SystemObject, isLoaded)
{
	Handler<SystemObject>(self)->system.isLoaded(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, isWide)
{
	return heap.newBooleanObject(Handler<SystemObject>(self)->system.isWide());
}
DEF_HOOK_SETTER(SystemObject, isWide)
{
	Handler<SystemObject>(self)->system.isWide(cast<bool>(obj->index(0)));
}
DEF_HOOK_GETTER(SystemObject, lastVideo)
{
	return heap.newStringObject(Handler<SystemObject>(self)->system.lastVideo());
}
DEF_HOOK_SETTER(SystemObject, lastVideo)
{
	Handler<SystemObject>(self)->system.lastVideo(cast<std::string>(obj->index(0)));
}

}}
