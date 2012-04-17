/*
 * Layer.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "Layer.h"

namespace saccubus {
namespace layer {

Layer::Layer(logging::Logger& log, draw::Renderer* renderer)
:log(log)
{
	this->renderer(renderer);

}

Layer::~Layer() {
	// do nothing
}

}}
