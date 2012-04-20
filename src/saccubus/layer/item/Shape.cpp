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

#include "Shape.h"
#include "../../draw/NullSprite.h"
#include "../../draw/ShapeFactory.h"

namespace saccubus {
namespace layer {
namespace item {

Shape::Shape(::nekomata::system::System* system, draw::ShapeFactory* shapeFactory)
: ::nekomata::system::Shape(*system)
{
	this->shapeFactory(shapeFactory);

}

Shape::~Shape() {
}

draw::Sprite::Handler<draw::Sprite> Shape::createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx)
{
	return this->shapeFactory()->renderShape(ctx, this);
}

void Shape::onChanged()
{
	this->invalidate();
}


}}}
