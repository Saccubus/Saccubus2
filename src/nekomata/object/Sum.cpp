/*
 * Sum.cpp
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
	const std::vector<std::string>& vec = dynamic_cast<SumObject&>(self).sum->words();
	Object* const obj = heap.newObject();
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
		vec.push_back(obj->index(i)->toStringObject()->toString());
	}
	dynamic_cast<SumObject&>(self).sum->words(vec);
}

SumObject::SumObject(SumObject& parent, int hash, std::tr1::shared_ptr<system::Sum> sum)
:HookableObject(parent, hash), sum(sum)
{

}
SumObject::~SumObject()
{

}


}
}


