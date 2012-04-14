/*
 * CommentLayer.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef COMMENTLAYER_H_
#define COMMENTLAYER_H_

#include "Layer.h"

namespace saccubus {
namespace layer {

class CommentLayer: public saccubus::layer::Layer {
public:
	CommentLayer();
	virtual ~CommentLayer();
public:
	virtual void draw(float vpos, draw::Canvas* canvas);
};

}}

#endif /* COMMENTLAYER_H_ */
