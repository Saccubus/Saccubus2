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

#ifndef CONTEXT_ITEM_H_
#define CONTEXT_ITEM_H_

#include "../../draw/Sprite.h"

namespace saccubus {
namespace layer {
namespace item {

class Item {
public:
	Item();
	virtual ~Item();
private:
	virtual draw::Sprite::Handler<draw::Sprite> querySprite(draw::ShapeFactory* shapeFactory, draw::CommentFactory* commentFactory) = 0;
	virtual bool onClick(float x, float y) = 0;
};

}}}
#endif /* CONTEXT_ITEM_H_ */
