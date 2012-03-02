/*
 * Cast.cpp
 *
 *  Created on: 2012/03/01
 *      Author: psi
 */

#include "Object.h"
#include "Cast.h"

namespace nekomata{
namespace object
{

template <>
double cast<double>(Handler<Object> const obj)
{
	return obj->toNumeric();
}
template <>
std::string cast<std::string>(Handler<Object> const obj)
{
	return obj->toString();
}
template<>
bool cast<bool>(Handler<Object> const obj)
{
	return obj->toBool();
}
template<>
std::vector<std::tr1::shared_ptr<system::Sum> > cast<std::vector<std::tr1::shared_ptr<system::Sum> > >(Handler<Object> const obj)
{
	std::vector<std::tr1::shared_ptr<system::Sum> > vec;
	const size_t max = obj->size();
	for(size_t i=0;i<max;++i){
		Handler<SumObject> const sumObj(obj->index(i));
		if(sumObj){
			vec.push_back(sumObj->getSum());
		}
	}
	return vec;
}

template<>
std::vector<std::string> cast<std::vector<std::string> >(Handler<Object> const obj)
{
	std::vector<std::string> vec;
	const size_t max = obj->size();
	for(size_t i=0;i<max;++i){
		vec.push_back(obj->index(i)->toString());
	}
	return vec;
}

std::string opt(Handler<Object> const obj, const std::string& key, const std::string& def)
{
	if(obj->has(key)){
		return cast<std::string>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(Handler<Object> const obj, size_t index, const std::string& def)
{
	if(obj->has(index)){
		return cast<std::string>(obj->index(index));
	}else{
		return def;
	}
}

}}
