/*
 * Handler.h
 *
 *  Created on: 2012/03/01
 *      Author: psi
 */

#ifndef HANDLER_H_
#define HANDLER_H_

namespace nekomata {
namespace object {

template<typename T>
class Handler
{
private:
	T* const obj;
public:
	Handler(T* const _obj):obj(_obj){
		obj->incNativeRef();
	}
	T* operator->()
	{
		return obj;
	}
	~Handler(){
		obj->decNativeRef();
	}
};

}
}
#endif /* HANDLER_H_ */
