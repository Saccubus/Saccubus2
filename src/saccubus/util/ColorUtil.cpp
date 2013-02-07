/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
