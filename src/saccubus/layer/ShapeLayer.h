/*
 * ShapeLayer.h
 *
 *  Created on: 2012/04/17
 *      Author: psi
 */

#ifndef SHAPELAYER_H_
#define SHAPELAYER_H_

#include "Layer.h"

namespace saccubus {
namespace layer {


class ShapeLayer: public saccubus::layer::Layer {
public:
	ShapeLayer(logging::Logger& log, draw::Renderer* renderer);
	virtual ~ShapeLayer();
public:
	virtual void draw(float vpos);
};

}}
#endif /* SHAPELAYER_H_ */
