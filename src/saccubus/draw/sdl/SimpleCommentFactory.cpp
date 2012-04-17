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
#include "SimpleCommentFactory.h"
#include "Renderer.h"
#include "Sprite.h"
#include "../../layer/item/Comment.h"

namespace saccubus {
namespace draw {
namespace sdl {

const double SimpleCommentFactory::ShadowWidth = 5.0;

SimpleCommentFactory::SimpleCommentFactory(logging::Logger& log, sdl::Renderer* renderer)
:CommentFactory(log, renderer)
{
#ifdef WIN32
	{
		LOGFONTW logf;
		memset(&logf, 0, sizeof(LOGFONTW));
		logf.lfCharSet=DEFAULT_CHARSET;
		cairo_font_face_t* ft = cairo_win32_font_face_create_for_logfontw(&logf);
		this->face(ft);
	}
#else
	{ /* パターンの作成 */
		FcPattern* pattern = FcPatternCreate();
		this->pattern(pattern);
	}
	{ /* パターンを設定 */
		FcPatternAddString( this->pattern(), FC_LANG, (const FcChar8*)"ja" );
		FcPatternAddString( this->pattern(), FC_FAMILY, (FcChar8*)"gothic");
		cairo_font_options_t* opt = cairo_font_options_create();
		cairo_font_options_set_subpixel_order(opt, CAIRO_SUBPIXEL_ORDER_RGB);
		cairo_font_options_set_antialias(opt, CAIRO_ANTIALIAS_DEFAULT);
		cairo_ft_font_options_substitute(opt, this->pattern());
		cairo_font_options_destroy(opt);
	}
	{ /* フェースの作成 */
		cairo_font_face_t* ft = cairo_ft_font_face_create_for_pattern(this->pattern());
		this->face(ft);
	}
#endif
	{
		this->emptySurface(cairo_image_surface_create(CAIRO_FORMAT_RGB24, 10, 10));
		this->emptyCairo(cairo_create(this->emptySurface()));
	}
}

SimpleCommentFactory::~SimpleCommentFactory() {
	cairo_destroy(this->emptyCairo());
	this->emptyCairo(0);
	cairo_surface_destroy(this->emptySurface());
	this->emptySurface(0);
	cairo_font_face_destroy(this->face());
	this->face(0);
#ifdef WIN32
	// do nothing!
#else
	FcPatternDestroy(this->pattern());
	this->pattern(0);
#endif
}


void SimpleCommentFactory::setupCairo(cairo_t* cairo, const saccubus::layer::item::Comment* comment, float factor)
{
	cairo_identity_matrix(cairo);
	cairo_scale(cairo, factor, factor);
	cairo_set_font_face(cairo, this->face());
	cairo_set_font_size(cairo, comment->size());
	cairo_move_to(cairo, 0, 0);
}

void SimpleCommentFactory::setColor(cairo_t* cairo, unsigned int color)
{
	unsigned int r = (color & 0xff0000) >> 16;
	unsigned int g = (color & 0x00ff00) >> 8;
	unsigned int b = (color & 0x0000ff) >> 0;
	float red = r/255.0f;
	float green = g/255.0f;
	float blue = b/255.0f;
	cairo_set_source_rgba(cairo, red, green, blue, 1);
}

saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> SimpleCommentFactory::renderComment(const saccubus::layer::item::Comment* comment, float factor)
{
	double x;
	double y;
	int width;
	int height;
	cairo_text_extents_t ext;
	{ /* 大きさを測定 */
		this->setupCairo(this->emptyCairo(), comment, factor);
		cairo_text_extents(this->emptyCairo(), comment->message().c_str(), &ext);
		x = -ext.x_bearing+ShadowWidth/2;
		y = -ext.y_bearing+ShadowWidth/2;
		double w = ext.width+ShadowWidth;
		double h = ext.height+ShadowWidth;
		//このwとhは論理座標なので、実際の大きさを取得するために変換してもらう。
		cairo_user_to_device_distance(this->emptyCairo(), &w, &h);
		width = std::ceil(w);
		height = std::ceil(h);
	}
	Sprite::Handler<RawSprite> spr = this->renderer()->queryRawSprite(width, height);
	{ /* 実際にレンダリング */
		RawSprite::Session session(spr);
		cairo_surface_t* surface = cairo_image_surface_create_for_data(
						reinterpret_cast<unsigned char*>(session.data()),
						CAIRO_FORMAT_ARGB32,
						session.width(),
						session.height(),
						session.stride()
				);

		cairo_t* cairo = cairo_create(surface);
		this->setupCairo(cairo, comment, factor);

		cairo_move_to(cairo, x, y);
		cairo_text_path(cairo, comment->message().c_str());

		this->setColor(cairo, comment->shadowColor());
		cairo_set_line_width(cairo, ShadowWidth);
		cairo_stroke_preserve(cairo);

		this->setColor(cairo, comment->color());
		cairo_fill(cairo);

		cairo_destroy(cairo);

		cairo_surface_destroy(surface);

	}
	return saccubus::draw::Sprite::Handler<saccubus::draw::Sprite>(spr);
}

}}}
