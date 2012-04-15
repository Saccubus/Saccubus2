/*
 * Layer.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "Layer.h"

namespace saccubus {
namespace layer {

Layer::Layer(draw::Renderer* renderer){
	this->renderer(renderer);

}

Layer::~Layer() {
	// do nothing
}

}}
