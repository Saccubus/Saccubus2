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

#include <cmath>
#include <cairo/cairo.h>
#include "SimpleShapeFactory.h"
#include "../../util/ColorUtil.h"

namespace saccubus {
namespace draw {
namespace cairo {

SimpleShapeFactory::SimpleShapeFactory(logging::Logger& log, cairo::Renderer* renderer)
:ShapeFactory(log, renderer)
{
	// TODO Auto-generated constructor stub

}

SimpleShapeFactory::~SimpleShapeFactory() {
	// TODO Auto-generated destructor stub
}

Sprite::Handler<draw::Sprite> SimpleShapeFactory::renderButton(int w, int h, unsigned int color, unsigned int hoverColor)
{

}
Sprite::Handler<draw::Sprite> SimpleShapeFactory::renderShape(const nekomata::system::Shape* const shape)
{
	const int w = std::ceil(shape->width());
	const int h = std::ceil(shape->height());
	Sprite::Handler<RawSprite> spr = this->renderer()->queryRawSprite(w, h);
	{
		RawSprite::Session session(spr);
		cairo_surface_t* surf = cairo_image_surface_create_for_data(
				reinterpret_cast<unsigned char*>(session.data()),
				CAIRO_FORMAT_ARGB32, session.width(), session.height(), session.stride());
		cairo_t* cairo = cairo_create(surf);

		// 使い回しデータである可能性があるので、クリアする
		cairo_set_operator(cairo, CAIRO_OPERATOR_CLEAR);
		cairo_set_source_rgba(cairo, 0, 0, 0, 0);
		cairo_paint(cairo);
		cairo_set_operator(cairo, CAIRO_OPERATOR_OVER);

		{
			float r,g,b;
			util::decodeColor(shape->color(), &r, &g, &b);
			cairo_set_source_rgba(cairo, r, g, b, (100.0f-shape->alpha())/100.0f);
		}
		if(shape->shape()=="circle"){
			const double hw=w/2.0f;
			cairo_scale(cairo, 1, (float)h/w);
			cairo_arc(cairo, hw, hw, hw, 0, M_PI*2);
			cairo_fill(cairo);
		}else if(shape->shape()=="rect"){
			cairo_paint(cairo);
		}

		cairo_destroy(cairo);

		cairo_surface_write_to_png(surf, "image.png");

		cairo_surface_destroy(surf);
	}
	return spr;
}

}}}
