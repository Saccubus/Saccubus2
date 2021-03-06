/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <nekomata/system/System.h>
#include <cinamo/String.h>
#include "SystemObject.h"
#include "Heap.h"
#include "Cast.h"

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

LabelObject::LabelObject(LabelObject& parent, int hash, Handler<system::Label> label)
:HookableObject(parent, hash), label(label)
{

}

Handler<system::Label> LabelObject::getLabel(){
	return label;
}

std::string LabelObject::toString()
{
	return cinamo::format("<<LabelObject:%d>>", getHash());
}

//---------------------------------------------------------------------------------------------------------------------

ReplaceObject::ReplaceObject(Object& parent)
:HookableObject(parent), replace((system::Replace*)0)
{
	ADD_HOOK_ACCESSOR(src);
	ADD_HOOK_ACCESSOR(dest);
	ADD_HOOK_ACCESSOR(enabled);
	ADD_HOOK_ACCESSOR(target);
	ADD_HOOK_ACCESSOR(fill);
	ADD_HOOK_ACCESSOR(partial);
	ADD_HOOK_ACCESSOR(color);
	ADD_HOOK_ACCESSOR(size);
	ADD_HOOK_ACCESSOR(pos);
}
DEF_HOOK_ACCESSOR_STR(ReplaceObject, src, replace);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, dest, replace);
DEF_HOOK_ACCESSOR_BOOL(ReplaceObject, enabled, replace);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, target, replace);
DEF_HOOK_ACCESSOR_BOOL(ReplaceObject, fill, replace);
DEF_HOOK_ACCESSOR_BOOL(ReplaceObject, partial, replace);
DEF_HOOK_ACCESSOR_INT(ReplaceObject, color, replace, unsigned int);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, size, replace);
DEF_HOOK_ACCESSOR_STR(ReplaceObject, pos, replace);

ReplaceObject::ReplaceObject(ReplaceObject& parent, int hash, Handler<system::Replace> replace)
:HookableObject(parent, hash), replace(replace)
{

}

Handler<system::Replace> ReplaceObject::getReplace(){
	return replace;
}
std::string ReplaceObject::toString()
{
	return cinamo::format("<<ReplaceObject:%d>>", getHash());
}

//---------------------------------------------------------------------------------------------------------------------
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

ShapeObject::ShapeObject(ShapeObject& parent, int hash, Handler<system::Shape> shape)
:HookableObject(parent, hash), shape(shape)
{

}

Handler<system::Shape> ShapeObject::getShape(){
	return shape;
}

std::string ShapeObject::toString()
{
	return cinamo::format("<<ShapeObject:%d>>", getHash());
}

//---------------------------------------------------------------------------------------------------------------------
SumObject::SumObject(Object& parent)
:HookableObject(parent), sum((system::Sum*)0)
{
	ADD_HOOK_ACCESSOR(x);
	ADD_HOOK_ACCESSOR(y);
	ADD_HOOK_ACCESSOR(size);
	ADD_HOOK_ACCESSOR(color);
	ADD_HOOK_ACCESSOR(visible);
	ADD_HOOK_ACCESSOR(enabled);
	ADD_HOOK_ACCESSOR(pos);
	ADD_HOOK_ACCESSOR(asc);
	ADD_HOOK_ACCESSOR(unit);
	ADD_HOOK_ACCESSOR(buttononly);
	ADD_HOOK_ACCESSOR(words);
	ADD_HOOK_ACCESSOR(partial);
}
DEF_HOOK_ACCESSOR_DOUBLE(SumObject, x, sum);
DEF_HOOK_ACCESSOR_DOUBLE(SumObject, y, sum);
DEF_HOOK_ACCESSOR_DOUBLE(SumObject, size, sum);
DEF_HOOK_ACCESSOR_INT(SumObject, color, sum, unsigned int);
DEF_HOOK_ACCESSOR_BOOL(SumObject, visible, sum);
DEF_HOOK_ACCESSOR_BOOL(SumObject, enabled, sum);
DEF_HOOK_ACCESSOR_STR(SumObject, pos, sum);
DEF_HOOK_ACCESSOR_BOOL(SumObject, asc, sum);
DEF_HOOK_ACCESSOR_STR(SumObject, unit, sum);
DEF_HOOK_ACCESSOR_BOOL(SumObject, buttononly, sum);
DEF_HOOK_GETTER(SumObject, words)
{
	const std::vector<std::string>& vec = self.cast<SumObject>()->sum->words();
	const Handler<Object> obj(heap.newObject());
	for(std::vector<std::string>::const_iterator it = vec.begin();it != vec.end();++it)
	{
		obj->push(heap.newStringObject(*it));
	}
	return obj;
}
DEF_HOOK_SETTER(SumObject, words)
{
	std::vector<std::string> vec;
	for(size_t i = 0;i<obj->size();++i){
		vec.push_back(cast<std::string>(obj->index(i)));
	}
	self.cast<SumObject>()->sum->words(vec);
}
DEF_HOOK_ACCESSOR_BOOL(SumObject, partial, sum);

SumObject::SumObject(SumObject& parent, int hash, Handler<system::Sum> sum)
:HookableObject(parent, hash), sum(sum)
{

}

Handler<system::Sum> SumObject::getSum(){
	return sum;
}

std::string SumObject::toString()
{
	return cinamo::format("<<SumObject:%d>>", getHash());
}

//---------------------------------------------------------------------------------------------------------------------
SumResultObject::SumResultObject(Object& parent)
:HookableObject(parent), sumResult((system::SumResult*)0)
{
	ADD_HOOK_ACCESSOR(x);
	ADD_HOOK_ACCESSOR(y);
	ADD_HOOK_ACCESSOR(color);
	ADD_HOOK_ACCESSOR(visible);
	ADD_HOOK_ACCESSOR(pos);
	ADD_HOOK_ACCESSOR(unit);
	ADD_HOOK_ACCESSOR(asc);
	ADD_HOOK_ACCESSOR(sum);
}
DEF_HOOK_ACCESSOR_DOUBLE(SumResultObject, x, sumResult);
DEF_HOOK_ACCESSOR_DOUBLE(SumResultObject, y, sumResult);
DEF_HOOK_ACCESSOR_INT(SumResultObject, color, sumResult, unsigned int);
DEF_HOOK_ACCESSOR_BOOL(SumResultObject, visible, sumResult);
DEF_HOOK_ACCESSOR_STR(SumResultObject, pos, sumResult);
DEF_HOOK_ACCESSOR_BOOL(SumResultObject, asc, sumResult);
DEF_HOOK_ACCESSOR_STR(SumResultObject, unit, sumResult);
DEF_HOOK_GETTER(SumResultObject, sum)
{
	const std::vector<Handler<system::Sum> >& vec = self.cast<SumResultObject>()->sumResult->sum();
	const Handler<Object> obj(heap.newObject());
	for(std::vector<Handler<system::Sum> >::const_iterator it = vec.begin();it != vec.end();++it)
	{
		obj->push(heap.newSumObject(*it));
	}
	return obj;
}
DEF_HOOK_SETTER(SumResultObject, sum)
{
	std::vector<Handler<system::Sum> > vec;
	for(size_t i = 0;i<obj->size();++i){
		const Handler<SumObject> sumObj(obj->index(i).cast<SumObject>());
		if(sumObj){
			vec.push_back(sumObj->getSum());
		}
	}
	self.cast<SumResultObject>()->sumResult->sum(vec);
}

SumResultObject::SumResultObject(SumResultObject& parent, int hash, Handler<system::SumResult> sumResult)
:HookableObject(parent, hash), sumResult(sumResult)
{

}

Handler<system::SumResult> SumResultObject::getSumResult(){
	return sumResult;
}

std::string SumResultObject::toString()
{
	return cinamo::format("<<SumResultObject:%d>>", getHash());
}


}}
