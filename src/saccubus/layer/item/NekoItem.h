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

#ifndef Saccubus_NEKOITEM_H__CPP_
#define Saccubus_NEKOITEM_H__CPP_

#include <nekomata/system/System.h>
#include "Item.h"

namespace saccubus {
namespace layer {
namespace item {

class NekoItem: public saccubus::layer::item::Item {
public:
	enum PosX{
		CenterX,
		Right,
		Left
	};
	enum PosY{
		CenterY,
		Top,
		Bottom
	};
	DEF_ATTR_ACCESSOR(public, private, enum PosX, posX);
	DEF_ATTR_ACCESSOR(public, private, enum PosY, posY);
	DEF_ATTR_ACCESSOR(public, private, nekomata::system::Drawable*, drawable);
public:
	NekoItem(nekomata::system::Drawable* nekoDrawable);
	virtual ~NekoItem();
	virtual void invalidate();
};

}}}
#endif /* INCLUDE_GUARD */
