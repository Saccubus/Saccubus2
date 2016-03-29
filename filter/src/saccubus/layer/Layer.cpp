/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Layer.h"

namespace saccubus {
namespace layer {

Layer::Layer(cinamo::Logger& log)
:log(log)
{

}

void Layer::measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight)
{
	*measuredWidth = w;
	*measuredHeight = h;
}

Layer::~Layer() {
	// do nothing
}

}}
