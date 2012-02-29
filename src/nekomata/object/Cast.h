/*
 * Opt.h
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#ifndef CAST_H_
#define CAST_H_

#include <string>
#include <vector>
#include "Object.h"

namespace nekomata{
namespace object
{

template <typename T>
T cast(Object* const obj)
{
	return static_cast<T>(obj->toNumericObject()->toNumeric());
}
template <>
double cast<double>(Object* const obj)
{
	return obj->toNumericObject()->toNumeric();
}
template <>
std::string cast<std::string>(Object* const obj)
{
	return obj->toStringObject()->toString();
}
template<>
bool cast<bool>(Object* const obj)
{
	return obj->toBooleanObject()->toBool();
}
template<>
std::vector<std::tr1::shared_ptr<system::Sum> > cast<std::vector<std::tr1::shared_ptr<system::Sum> > >(Object* const obj)
{
	std::vector<std::tr1::shared_ptr<system::Sum> > vec;
	const size_t max = obj->size();
	for(size_t i=0;i<max;++i){
		SumObject* const sumObj = dynamic_cast<SumObject*>(obj->index(i));
		if(sumObj){
			vec.push_back(sumObj->getSum());
		}
	}
	return vec;
}

template<>
std::vector<std::string> cast<std::vector<std::string> >(Object* const obj)
{
	std::vector<std::string> vec;
	const size_t max = obj->size();
	for(size_t i=0;i<max;++i){
		vec.push_back(obj->index(i)->toStringObject()->toString());
	}
	return vec;
}

//---------------------------------------------------------------------------------------------------------------------

template <typename T>
T opt(Object* const obj, const std::string& key, const T& def)
{
	if(obj->has(key)){
		return cast<T>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(Object* const obj, const std::string& key, const std::string& def)
{
	if(obj->has(key)){
		return cast<std::string>(obj->getSlot(key));
	}else{
		return def;
	}
}
template <typename T>
T opt(Object* const obj, size_t index, const T& def)
{
	if(obj->has(index)){
		return cast<T>(obj->index(index));
	}else{
		return def;
	}
}
std::string opt(Object* const obj, size_t index, const std::string& def)
{
	if(obj->has(index)){
		return cast<std::string>(obj->index(index));
	}else{
		return def;
	}
}


}}

#endif /* CAST_H_ */
