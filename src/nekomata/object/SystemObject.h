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

#pragma once
#include <nekomata/system/System.h>
#include "Object.h"

namespace nekomata{
namespace object{
class SystemObject : public HookableObject
{
	system::System& system;
public:
	explicit SystemObject(Object& parent, system::System& system);
	virtual ~SystemObject();
public:
	void setChat(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no);
public:
	DEC_HOOK_ACCESSOR(commentColor);
	DEC_HOOK_ACCESSOR(commentPlace);
	DEC_HOOK_ACCESSOR(commentSize);
	DEC_HOOK_ACCESSOR(commentInvisible);
	DEC_HOOK_ACCESSOR(commentReverse);
	DEC_HOOK_ACCESSOR(defaultSage);
	DEC_HOOK_ACCESSOR(postDisabled);
	DEC_HOOK_ACCESSOR(seekDisabled);
	DEC_HOOK_ACCESSOR(isLoaded);
	DEC_HOOK_ACCESSOR(isWide);
	DEC_HOOK_ACCESSOR(lastVideo);
public:
	DEC_BUILTIN(drawShape);
	DEC_BUILTIN(drawText);
	DEC_BUILTIN(commentTrigger);
	DEC_BUILTIN(timer);
	DEC_BUILTIN(jump);
	DEC_BUILTIN(jumpCancel);
	DEC_BUILTIN(seek);
	DEC_BUILTIN(addMarker);
	DEC_BUILTIN(getMarker);
	DEC_BUILTIN(sum);
	DEC_BUILTIN(showResult);
	DEC_BUILTIN(replace);
	DEC_BUILTIN(screenWidth);
	DEC_BUILTIN(screenHeight);
	DEC_BUILTIN(addButton);
	DEC_BUILTIN(playStartTime);
	DEC_BUILTIN(BGM);
	DEC_BUILTIN(playBGM);
	DEC_BUILTIN(stopBGM);
	DEC_BUILTIN(addAtPausePoint);
	DEC_BUILTIN(addPostRoute);
	DEC_BUILTIN(CM);
	DEC_BUILTIN(playCM);
public:
	virtual std::string toString();
};

class ShapeObject : public HookableObject
{
private:
	Handler<system::Shape> shape;
public:
	explicit ShapeObject(Object& parent);
	explicit ShapeObject(ShapeObject& parent, int hash, Handler<system::Shape> shape);
	virtual ~ShapeObject();
	Handler<system::Shape> getShape();
public:
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(z);
	DEC_HOOK_ACCESSOR(shape);
	DEC_HOOK_ACCESSOR(width);
	DEC_HOOK_ACCESSOR(height);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(mask);
	DEC_HOOK_ACCESSOR(commentmask);
	DEC_HOOK_ACCESSOR(alpha);
	DEC_HOOK_ACCESSOR(rotation);
	DEC_HOOK_ACCESSOR(mover);
public:
	virtual std::string toString();
};

class SumObject : public HookableObject
{
private:
	Handler<system::Sum> sum;
public:
	explicit SumObject(Object& parent);
	explicit SumObject(SumObject& parent, int hash, Handler<system::Sum> sum);
	virtual ~SumObject();
	Handler<system::Sum> getSum();
public:
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(size);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(enabled);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(asc);
	DEC_HOOK_ACCESSOR(unit);
	DEC_HOOK_ACCESSOR(buttononly);
	DEC_HOOK_ACCESSOR(words);
	DEC_HOOK_ACCESSOR(partial);
public:
	virtual std::string toString();
};
class SumResultObject : public HookableObject
{
private:
	Handler<system::SumResult> sumResult;
public:
	explicit SumResultObject(Object& parent);
	explicit SumResultObject(SumResultObject& parent, int hash, Handler<system::SumResult> sumResult);
	virtual ~SumResultObject();
	Handler<system::SumResult> getSumResult();
public:
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(unit);
	DEC_HOOK_ACCESSOR(asc);
	DEC_HOOK_ACCESSOR(sum);
public:
	virtual std::string toString();
};
class LabelObject : public HookableObject
{
private:
	Handler<system::Label> label;
public:
	explicit LabelObject(Object& parent);
	explicit LabelObject(LabelObject& parent, int hash, Handler<system::Label> Label);
	virtual ~LabelObject();
	Handler<system::Label> getLabel();
public:
	DEC_HOOK_ACCESSOR(text);
	DEC_HOOK_ACCESSOR(x);
	DEC_HOOK_ACCESSOR(y);
	DEC_HOOK_ACCESSOR(z);
	DEC_HOOK_ACCESSOR(size);
	DEC_HOOK_ACCESSOR(pos);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(bold);
	DEC_HOOK_ACCESSOR(visible);
	DEC_HOOK_ACCESSOR(filter);
	DEC_HOOK_ACCESSOR(alpha);
	DEC_HOOK_ACCESSOR(mover);
public:
	virtual std::string toString();
};

class ReplaceObject : public HookableObject
{
private:
	Handler<system::Replace> replace;
public:
	explicit ReplaceObject(Object& parent);
	explicit ReplaceObject(ReplaceObject& parent, int hash, Handler<system::Replace> replace);
	virtual ~ReplaceObject();
	Handler<system::Replace> getReplace();
public:
	DEC_HOOK_ACCESSOR(src);
	DEC_HOOK_ACCESSOR(dest);
	DEC_HOOK_ACCESSOR(enabled);
	DEC_HOOK_ACCESSOR(target);
	DEC_HOOK_ACCESSOR(fill);
	DEC_HOOK_ACCESSOR(partial);
	DEC_HOOK_ACCESSOR(color);
	DEC_HOOK_ACCESSOR(size);
	DEC_HOOK_ACCESSOR(pos);
public:
	virtual std::string toString();
};

}}
