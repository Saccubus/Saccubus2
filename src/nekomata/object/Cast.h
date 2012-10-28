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
