/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "ColorUtil.h"

namespace saccubus {
namespace util {

void decodeColor(unsigned int color, float* r, float* g, float* b)
{
	unsigned int ir = (color & 0xff0000) >> 16;
	unsigned int ig = (color & 0x00ff00) >> 8;
	unsigned int ib = (color & 0x0000ff) >> 0;
	*r = ir/255.0f;
	*g = ig/255.0f;
	*b = ib/255.0f;
}

}
}
