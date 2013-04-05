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

std::string opt(const Handler<Object> obj, const std::string& key, const std::string& def)
{
	if(obj->has(key)){
		return cast<std::string>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(const Handler<Object> obj, size_t index, const std::string& def)
{
	if(obj->has(index)){
		return cast<std::string>(obj->index(index));
	}else{
		return def;
	}
}

}}
