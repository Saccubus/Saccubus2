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
#include "../Context.h"
#include "../LayerdSprite.h"
#include "../../layer/item/Comment.h"
#include "../../layer/item/Label.h"
#include "../NullSprite.h"
#include "../../logging/Logger.h"
#include "../../util/ColorUtil.h"
#include "../../util/StringUtil.h"

namespace saccubus {
namespace draw {
namespace cairo {

const std::string TAG("SimpleCommentFactory");

const double SimpleCommentFactory::ShadowWidth = 5.0;

SimpleCommentFactory::SimpleCommentFactory(logging::Logger& log, cairo::Renderer* renderer, const std::map<std::string, std::string> & config)
:CommentFactory(log, renderer)
{
#if USE_WINDOWS_NATIVE
	{
		LOGFONTW logf;
		memset(&logf, 0, sizeof(LOGFONTW));
		logf.lfEscapement = 0;
		logf.lfOrientation = 0;
		logf.lfWeight = FW_DONTCARE;
		logf.lfItalic = FALSE;
		logf.lfUnderline = FALSE;
		logf.lfStrikeOut = FALSE;
		logf.lfCharSet=SHIFTJIS_CHARSET;
		logf.lfOutPrecision = OUT_STROKE_PRECIS;
		logf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logf.lfQuality = ANTIALIASED_QUALITY;
		logf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		wcscpy(logf.lfFaceName,  L"MS UI Gothic");
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
		FcPatternAddString( this->pattern(), FC_FAMILY, (FcChar8*)"MS UI Gothic");
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
#if USE_WINDOWS_NATIVE
	// do nothing!
#else
	FcPatternDestroy(this->pattern());
	this->pattern(0);
#endif
}


void SimpleCommentFactory::setupCairo(std::shared_ptr<saccubus::draw::Context> ctx, cairo_t* cairo, double fontSize)
{
	cairo_identity_matrix(cairo);
	const double factor = ctx->factor();
	cairo_scale(cairo, factor, factor);
	cairo_set_font_face(cairo, this->face());
	cairo_set_font_size(cairo, fontSize);
	cairo_move_to(cairo, 0, 0);
}

void SimpleCommentFactory::setColor(cairo_t* cairo, unsigned int color)
{
	float r,g,b;
	util::decodeColor(color, &r, &g, &b);
	cairo_set_source_rgba(cairo, r, g, b, 1);
}

saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> SimpleCommentFactory::renderLine(std::shared_ptr<saccubus::draw::Context> ctx, const std::string& str, bool fitToScreen, unsigned long color, unsigned long shadowColor, double size)
{
	double scale = 1.0;
	double x = 0;
	double y = 0;
	int width = 0;
	int height = 0;
	{ /* 大きさを測定 */
		cairo_text_extents_t ext;
		cairo_font_extents_t fext;
		this->setupCairo(ctx, this->emptyCairo(), size);
		cairo_text_extents(this->emptyCairo(), (str).c_str(), &ext);
		x = ShadowWidth/2;
		double w = ext.x_advance+ShadowWidth;
		y = -ext.y_bearing+ShadowWidth/2;
		double h = ext.height+ext.y_advance+ShadowWidth;
		//このwとhは論理座標なので、実際の大きさを取得するために変換してもらう。
		cairo_user_to_device_distance(this->emptyCairo(), &w, &h);
		if(fitToScreen){
			scale = std::min(w, (double)ctx->width()) / w;
		}
		width = std::ceil(w*scale);
		height = std::ceil(h*scale);
		if(ext.width <= 1 || ext.height <= 1){
			cairo_font_extents(this->emptyCairo(), &fext);
			double fontW = fext.max_x_advance;
			double fontH = fext.max_y_advance + fext.height;
			cairo_user_to_device_distance(this->emptyCairo(), &fontW, &fontH);
			return NullSprite::newInstance(width, std::ceil(fontH+ShadowWidth));
		}
	}
	Sprite::Handler<RawSprite> spr = this->renderer()->queryRawSprite(width, height);
	{ /* 実際にレンダリング */
		//log.d(TAG, "Rendering: %s", comment->message().c_str());
		RawSprite::Session session(spr);
		cairo_surface_t* surface = cairo_image_surface_create_for_data(
						reinterpret_cast<unsigned char*>(session.data()),
						CAIRO_FORMAT_ARGB32,
						session.width(),
						session.height(),
						session.stride()
				);
		cairo_t* cairo = cairo_create(surface);
		this->setupCairo(ctx, cairo, size);
		cairo_scale(cairo, scale, scale);

		/* サーフェイスの中身を一旦すべて削除 */
		cairo_set_operator(cairo, CAIRO_OPERATOR_CLEAR);
		cairo_paint(cairo);

		cairo_set_operator(cairo, CAIRO_OPERATOR_OVER);
		cairo_move_to(cairo, x, y);

		cairo_text_path(cairo, str.c_str());

		this->setColor(cairo, shadowColor);
		cairo_set_line_width(cairo, ShadowWidth);
		cairo_stroke_preserve(cairo);

		this->setColor(cairo, color);
		cairo_fill(cairo);

		cairo_destroy(cairo);

		cairo_surface_destroy(surface);

	}
	return saccubus::draw::Sprite::Handler<saccubus::draw::Sprite>(spr);
}

saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> SimpleCommentFactory::renderLines(std::shared_ptr<saccubus::draw::Context> ctx, const std::string& str, bool fitToScreen, unsigned long color, unsigned long shadowColor, double size)
{
	std::vector<std::string> lines;
	util::splitLine(str, lines);
	if(lines.size() <= 0){
		return renderLine(ctx, str, fitToScreen, color, shadowColor, size);
	}else if(lines.size() == 1){
		return renderLine(ctx, lines.front(), fitToScreen, color, shadowColor, size);
	}
	saccubus::draw::Sprite::Handler<saccubus::draw::LayerdSprite> spr = saccubus::draw::LayerdSprite::newInstance();
	int y = 0;
	for(std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it){
		saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> line = renderLine(ctx, *it, fitToScreen, color, shadowColor, size);
		spr->addSprite(0, y, line);
		y += line->height();
	}
	return spr;
}

saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> SimpleCommentFactory::renderCommentText(std::shared_ptr<saccubus::draw::Context> ctx, const saccubus::layer::item::Comment* comment)
{
	return renderLines(ctx, comment->message(), comment->placeY() != layer::item::Comment::Middle, comment->color(), comment->shadowColor(), comment->size());
}

saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> SimpleCommentFactory::renderLabelText(std::shared_ptr<saccubus::draw::Context> ctx, const saccubus::layer::item::Label* label)
{
	return renderLines(ctx, label->text(), false, label->color(), 0x000000, label->size());
}

}}}
