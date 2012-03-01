/*
 * Handler.cpp
 *
 *  Created on: 2012/03/01
 *      Author: psi
 */

#include "Handler.h"
#include "Object.h"

namespace nekomata {
namespace object {

Handler::Handler(Object* const _obj):obj(_obj){
	obj->incNativeRef();
};
Object* Handler::operator->()
{
	return obj;
}
Handler::~Handler(){
	obj->decNativeRef();
}


} /* namespace object */
} /* namespace nekomata */
