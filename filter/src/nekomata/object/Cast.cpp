/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "Object.h"
#include "SystemObject.h"
#include "Cast.h"

namespace nekomata{
namespace object
{

template <>
double cast<double>(const Handler<Object> obj)
{
	return obj->toNumeric();
}
template <>
std::string cast<std::string>(const Handler<Object> obj)
{
	return obj->toString();
}
template<>
bool cast<bool>(const Handler<Object> obj)
{
	return obj->toBool();
}
template<>
std::vector<Handler<system::Sum> > cast<std::vector<Handler<system::Sum> > >(const Handler<Object> obj)
{
	std::vector<Handler<system::Sum> > vec;
	const size_t max = obj->size();
	for(size_t i=0;i<max;++i){
		const Handler<SumObject> sumObj(obj->index(i).tryCast<SumObject>());
		if(sumObj){
			vec.push_back(sumObj->getSum());
		}
	}
	return vec;
}

template<>
std::vector<std::string> cast<std::vector<std::string> >(const Handler<Object> obj)
{
	std::vector<std::string> vec;
	const size_t max = obj->size();
	for(size_t i=0;i<max;++i){
		vec.push_back(obj->index(i)->toString());
	}
	return vec;
}

std::string opt(const Handler<Object> obj, std::string const& key, std::string const& def)
{
	if(obj->has(key)){
		return cast<std::string>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(const Handler<Object> obj, size_t index, std::string const& def)
{
	if(obj->has(index)){
		return cast<std::string>(obj->index(index));
	}else{
		return def;
	}
}

}}
