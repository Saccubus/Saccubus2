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

#ifndef Saccubus_SHAPEFACTORY_H__CPP_
#define Saccubus_SHAPEFACTORY_H__CPP_
#include "RawSprite.h"
#include "../util/ClassAccessor.h"
#include <nekomata/system/System.h>

namespace saccubus {
namespace draw {

class ShapeFactory {
private:
	DEF_ATTR_ACCESSOR(protected, private, Renderer*, renderer);
protected:
	logging::Logger& log;
public:
	ShapeFactory(logging::Logger& log, Renderer* renderer);
	virtual ~ShapeFactory();
public:
	virtual Sprite::Handler<Sprite> renderButton(int w, int h, unsigned int color, unsigned int hoverColor) = 0;
	virtual Sprite::Handler<Sprite> renderShape(const nekomata::system::Shape* const shape) = 0;
};

}}
#endif /* INCLUDE_GUARD */
