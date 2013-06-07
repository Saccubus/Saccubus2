/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <vector>
#include "Object.h"

namespace nekomata{
namespace object
{

template <typename T>
T cast(const Handler<Object> obj)
{
	return static_cast<T>(obj->toNumeric());
}
template<> double cast<double>(const Handler<Object> obj);
template<> std::string cast<std::string>(const Handler<Object> obj);
template<> bool cast<bool>(const Handler<Object> obj);
template<> std::vector<Handler<system::Sum> > cast<std::vector<Handler<system::Sum> > >(const Handler<Object> obj);
template<> std::vector<std::string> cast<std::vector<std::string> >(const Handler<Object> obj);

//---------------------------------------------------------------------------------------------------------------------

template <typename T>
T opt(const Handler<Object> obj, const std::string& key, const T& def)
{
	if(obj->has(key)){
		return cast<T>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(const Handler<Object> obj, const std::string& key, const std::string& def);
template <typename T>
T opt(Object* const obj, size_t index, const T& def)
{
	if(obj->has(index)){
		return cast<T>(obj->index(index));
	}else{
		return def;
	}
}
std::string opt(const Handler<Object> obj, size_t index, const std::string& def);


}}
