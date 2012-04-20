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

#include "Item.h"

namespace saccubus {
namespace layer {
namespace item {

Item::Item() {
	// TODO Auto-generated constructor stub

}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

draw::Sprite::Handler<draw::Sprite> Item::querySprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx)
{
	if(!sprite){
		sprite = this->createSprite(ctx);
	}
	return sprite;
}
void Item::invalidate()
{
	sprite.reset();
}

bool Item::onClick(){
	return false;
}

}}}
