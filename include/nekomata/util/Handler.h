/*
 * Handler.h
 *
 *  Created on: 2012/03/01
 *      Author: psi
 */

#ifndef UTIL_HANDLER_H_
#define UTIL_HANDLER_H_

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
#endif /* UTIL_HANDLER_H_ */
