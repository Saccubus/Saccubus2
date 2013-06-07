/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "ShapeFactory.h"

namespace saccubus {
namespace draw {

ShapeFactory::ShapeFactory(cinamo::Logger& log, Renderer* renderer)
:log(log){
	this->renderer(renderer);
}

ShapeFactory::~ShapeFactory() {
}

}}
