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
#include "./Context.h"
#include "../../util/ColorUtil.h"

namespace saccubus {
namespace draw {
namespace cairo {

SimpleShapeFactory::SimpleShapeFactory(logging::Logger& log, cairo::Renderer* renderer, const std::map<std::string, std::string> & config)
:ShapeFactory(log, renderer)
{
	/* 何も生成しないし何も設定しない */
}

SimpleShapeFactory::~SimpleShapeFactory()
{
}

Sprite::Handler<draw::Sprite> SimpleShapeFactory::renderButton(std::tr1::shared_ptr<saccubus::draw::Context> ctx, int _w, int _h, unsigned int color)
{
	const int w = std::ceil(_w * ctx->factor());
	const int h = std::ceil(_h * ctx->factor());
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
			util::decodeColor(color, &r, &g, &b);
			cairo_pattern_t *pat;

			pat = cairo_pattern_create_linear (0.0, 0.0,  0.0, h);
			cairo_pattern_add_color_stop_rgba (pat, 1, r/2, g/2, b/2, 1);
			cairo_pattern_add_color_stop_rgba (pat, 0, r, g, b, 1);
			if(w > h){
				cairo_move_to(cairo, h/2.0, h/2.0);
				cairo_line_to(cairo, w-(h/2.0), h/2.0);
				cairo_set_line_width(cairo, h);
			}else{
				cairo_move_to(cairo, w/2.0, w/2.0);
				cairo_line_to(cairo, w/2.0, h-(w/2.0));
				cairo_set_line_width(cairo, w);
			}
			cairo_set_line_cap(cairo, CAIRO_LINE_CAP_ROUND);
			cairo_set_source (cairo, pat);
			cairo_stroke (cairo);
			cairo_pattern_destroy (pat);
		}

		cairo_destroy(cairo);

		cairo_surface_destroy(surf);
	}
	return spr;
}
Sprite::Handler<draw::Sprite> SimpleShapeFactory::renderShape(std::tr1::shared_ptr<saccubus::draw::Context> ctx, const nekomata::system::Shape* const shape)
{
	const int w = std::ceil(shape->width() * ctx->factor());
	const int h = std::ceil(shape->height() * ctx->factor());
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

		cairo_surface_destroy(surf);
	}
	return spr;
}

}}}
