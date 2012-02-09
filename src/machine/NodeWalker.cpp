/*
 * NodeWalker.cpp
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#include "NodeWalker.h"
#include "../tree/Node.h"

namespace machine
{
void NodeWalker::eval(const tree::Node& node){
	node.accept(*this);
}


} /* namespace machine */
