/*
 * NekomataLayer.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef NEKOMATALAYER_H_
#define NEKOMATALAYER_H_

#include "Layer.h"

namespace saccubus {
namespace layer {

class NekomataLayer: public saccubus::layer::Layer {
public:
	NekomataLayer();
	virtual ~NekomataLayer();
public:
	virtual void draw(float vpos, draw::Renderer* renderer);
};

}}
#endif /* NEKOMATALAYER_H_ */
