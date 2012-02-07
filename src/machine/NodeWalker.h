/*
 * NodeWalker.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef NODEWALKER_H_
#define NODEWALKER_H_
#include "../tree/Node.h"

namespace tree{
	class Node;
}

namespace machine
{

class NodeWalker{
public:
	NodeWalker();
	virtual ~NodeWalker();
	void walk(tree::Node* node);
};

} /* namespace machine */
#endif /* NODEWALKER_H_ */
