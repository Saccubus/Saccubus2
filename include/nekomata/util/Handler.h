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
#include <typeinfo>
#include "../logging/Exception.h"

namespace nekomata {
namespace util {

template<typename T>
class Handler
{
private:
	T* obj;
public:
	Handler(const Handler<T>& _h):obj(_h.obj){
		if(this->obj != ((T*)0)){
			this->obj->incNativeRef();
		}
	}
	explicit Handler(T* const _obj):obj(_obj){
		if(this->obj != ((T*)0)){
			this->obj->incNativeRef();
		}
	}
	Handler<T>& operator=(const Handler<T>& other)
	{
		if(other.obj != this->obj){
			if(this->obj != ((T*)0)){
				this->obj->decNativeRef();
			}
			if(other.obj != ((T*)0)){
				other.obj->incNativeRef();
			}
			this->obj = other.obj;
		}
		return *this;
	}
	T* operator->() const
	{
		return obj;
	}
	template <typename U>
	operator Handler<U> (void) const
	{
		U* const ptr = dynamic_cast<U*>(this->obj);
		if(ptr == ((U*)0)){
			throw logging::Exception(__FILE__, __LINE__, "Invalid dynamic cast from %s to %s", typeid(this->obj).name(), typeid(U).name());
		}
		return Handler<U>(ptr);
	}
	operator bool (void) const
	{
		 return this->obj != ((T*)0);
	}
	T* get() const
	{
		return obj;
	}
	~Handler(){
		if(this->obj != ((T*)0)){
			this->obj->decNativeRef();
		}
	}
};

}}
