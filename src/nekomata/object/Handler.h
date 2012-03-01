/*
 * Handler.h
 *
 *  Created on: 2012/03/01
 *      Author: psi
 */

#ifndef HANDLER_H_
#define HANDLER_H_

#include "Object.h"

namespace nekomata {
namespace object {

class Handler
{
private:
	Object* const obj;
public:
	Handler(Object* const _obj);
	Object* operator->();
	~Handler();
};

}
}
#endif /* HANDLER_H_ */
