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
#pragma once
#include "Renderer.h"
#include "../ShapeFactory.h"

namespace saccubus {
namespace draw {
namespace cairo {

class SimpleShapeFactory: public saccubus::draw::ShapeFactory {
public:
	SimpleShapeFactory(logging::Logger& log, cairo::Renderer* renderer, const std::map<std::string, std::string> & config);
	virtual ~SimpleShapeFactory();
public:
	virtual Sprite::Handler<draw::Sprite> renderButton(std::tr1::shared_ptr<saccubus::draw::Context> ctx, int w, int h, unsigned int color);
	virtual Sprite::Handler<draw::Sprite> renderShape(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const nekomata::system::Shape* const shape);
};

}}}
