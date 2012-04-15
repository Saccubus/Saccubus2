/*
 * CommentLayer.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef COMMENTLAYER_H_
#define COMMENTLAYER_H_

#include <deque>
#include "Layer.h"

namespace saccubus {
namespace layer {

class CommentLayer: public saccubus::layer::Layer {
private:
	std::deque<context::Comment*> comments;
public:
	CommentLayer(draw::Renderer* renderer);
	virtual ~CommentLayer();
public:
	virtual void draw(float vpos);
};

}}

#endif /* COMMENTLAYER_H_ */
