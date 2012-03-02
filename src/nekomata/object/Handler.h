/*
 * Handler.h
 *
 *  Created on: 2012/03/01
 *      Author: psi
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include "../logging/Exception.h"

namespace nekomata {
namespace object {

template<typename T>
class Handler
{
private:
	T* obj;
public:
	Handler(const Handler<T>& _h):obj(_h.obj){
		if(obj != ((T*)0)){
			obj->incNativeRef();
		}
	}
	explicit Handler(T* const _obj):obj(_obj){
		if(obj != ((T*)0)){
			obj->incNativeRef();
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
			obj = other.obj;
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

}
}
#endif /* HANDLER_H_ */
