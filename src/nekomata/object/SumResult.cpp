/*
 * SumResult.cpp
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
	const std::vector<std::tr1::shared_ptr<system::Sum> >& vec = Handler<SumResultObject>(self)->sumResult->sum();
	const Handler<Object> obj(heap.newObject());
	for(std::vector<std::tr1::shared_ptr<system::Sum> >::const_iterator it = vec.begin();it != vec.end();++it)
	{
		obj->push(heap.newSumObject(*it));
	}
	return obj;
}
DEF_HOOK_SETTER(SumResultObject, sum)
{
	std::vector<std::tr1::shared_ptr<system::Sum> > vec;
	for(size_t i = 0;i<obj->size();++i){
		const Handler<SumObject> sumObj(obj->index(i));
		if(sumObj){
			vec.push_back(sumObj->getSum());
		}
	}
	Handler<SumResultObject>(self)->sumResult->sum(vec);
}

SumResultObject::SumResultObject(SumResultObject& parent, int hash, std::tr1::shared_ptr<system::SumResult> sumResult)
:HookableObject(parent, hash), sumResult(sumResult)
{

}
SumResultObject::~SumResultObject()
{

}


}
}


