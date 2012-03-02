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
T cast(Handler<Object> const obj)
{
	return static_cast<T>(obj->toNumeric());
}
template<> double cast<double>(Handler<Object> const obj);
template<> std::string cast<std::string>(Handler<Object> const obj);
template<> bool cast<bool>(Handler<Object> const obj);
template<> std::vector<std::tr1::shared_ptr<system::Sum> > cast<std::vector<std::tr1::shared_ptr<system::Sum> > >(Handler<Object> const obj);
template<> std::vector<std::string> cast<std::vector<std::string> >(Handler<Object> const obj);

//---------------------------------------------------------------------------------------------------------------------

template <typename T>
T opt(Handler<Object> const obj, const std::string& key, const T& def)
{
	if(obj->has(key)){
		return cast<T>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(Handler<Object> const obj, const std::string& key, const std::string& def);
template <typename T>
T opt(Object* const obj, size_t index, const T& def)
{
	if(obj->has(index)){
		return cast<T>(obj->index(index));
	}else{
		return def;
	}
}
std::string opt(Handler<Object> const obj, size_t index, const std::string& def);


}}

#endif /* CAST_H_ */
