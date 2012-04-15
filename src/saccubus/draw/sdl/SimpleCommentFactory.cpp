/*
 * SimpleCommentFactory.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include <cmath>
#include "SimpleCommentFactory.h"
#include "Renderer.h"
#include "Sprite.h"
#include "../../context/Comment.h"

namespace saccubus {
namespace draw {
namespace sdl {

const double SimpleCommentFactory::ShadowWidth = 5.0;

SimpleCommentFactory::SimpleCommentFactory(sdl::Renderer* renderer)
:CommentFactory(renderer)
{
	{
		FcPattern* pattern = FcPatternCreate();
		this->pattern(pattern);
	}
	{
		FcPatternAddString( this->pattern(), FC_LANG, (const FcChar8*)"ja" );
		FcPatternAddString( this->pattern(), FC_FAMILY, (FcChar8*)"gothic");
		cairo_font_options_t* opt = cairo_font_options_create();
		cairo_font_options_set_subpixel_order(opt, CAIRO_SUBPIXEL_ORDER_RGB);
		cairo_font_options_set_antialias(opt, CAIRO_ANTIALIAS_DEFAULT);
		cairo_ft_font_options_substitute(opt, this->pattern());
		cairo_font_options_destroy(opt);
	}
	{
		cairo_font_face_t* ft = cairo_ft_font_face_create_for_pattern(this->pattern());
		this->face(ft);
	}
	{
		this->emptySurface(cairo_image_surface_create(CAIRO_FORMAT_RGB24, 10, 10));
		this->emptyCairo(cairo_create(this->emptySurface()));
	}
}

SimpleCommentFactory::~SimpleCommentFactory() {
	cairo_font_face_destroy(this->face());
	this->face(0);
	FcPatternDestroy(this->pattern());
	this->pattern(0);
	cairo_destroy(this->emptyCairo());
	this->emptyCairo(0);
	cairo_surface_destroy(this->emptySurface());
	this->emptySurface(0);
}


void SimpleCommentFactory::setFont(cairo_t* cairo, const saccubus::context::Comment* comment)
{
	cairo_set_font_face(cairo, this->face());
	cairo_set_font_size(cairo, comment->size());
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

saccubus::draw::RawSprite::Handler SimpleCommentFactory::renderComment(const saccubus::context::Comment* comment)
{
	double x;
	double y;
	int w;
	int h;
	cairo_text_extents_t ext;
	{ /* 大きさを測定 */
		this->setFont(this->emptyCairo(), comment);
		cairo_move_to(this->emptyCairo(), 0, 0);
		cairo_text_extents(this->emptyCairo(), comment->message().c_str(), &ext);
		x = -ext.x_bearing+ShadowWidth/2;
		y = -ext.y_bearing+ShadowWidth/2;
		w = std::ceil(ext.width+ShadowWidth);
		h = std::ceil(ext.height+ShadowWidth);
	}
	RawSprite::Handler handler = this->renderer()->querySprite(w, h);
	{ /* 実際にレンダリング */
		sdl::Sprite* spr = dynamic_cast<sdl::Sprite*>(*handler);
		RawSprite::Session session(spr);
		cairo_surface_t* surface = cairo_image_surface_create_for_data(
						reinterpret_cast<unsigned char*>(session.data()),
						CAIRO_FORMAT_ARGB32,
						session.width(),
						session.height(),
						session.stride()
				);

		cairo_t* cairo = cairo_create(surface);

		this->setFont(cairo, comment);
		cairo_move_to(cairo, x, y);
		this->setColor(cairo, comment->color());
		cairo_show_text(cairo, comment->message().c_str());

		cairo_move_to(cairo, x, y);
		cairo_text_path(cairo, comment->message().c_str());

		this->setColor(cairo, comment->shadowColor());
		cairo_set_line_width(cairo, 5);
		cairo_stroke_preserve(cairo);

		this->setColor(cairo, comment->color());
		cairo_fill(cairo);

		cairo_destroy(cairo);

		cairo_surface_destroy(surface);

	}
	return handler;
}

}}}
