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

#define USE_WINDOWS_NATIVE (defined(WIN32) && (1))

#include <map>
#if USE_WINDOWS_NATIVE
#include <cairo/cairo-win32.h>
#else
#include <cairo/cairo-ft.h>
#endif
#include <fontconfig/fontconfig.h>
#include "../../classdefs.h"
#include "../CommentFactory.h"

namespace saccubus {
namespace draw {
namespace cairo {

class Renderer;
class ArtisticCommentFactory: public saccubus::draw::CommentFactory {
private:
	static const double ShadowWidth;
private:
#if !(USE_WINDOWS_NATIVE)
	DEF_ATTR_ACCESSOR(private, private, FcPattern*, pattern);
#endif
	DEF_ATTR_ACCESSOR(private, private, cairo_font_face_t*, face);
	DEF_ATTR_ACCESSOR(private, private, cairo_t*, emptyCairo);
	DEF_ATTR_ACCESSOR(private, private, cairo_surface_t*, emptySurface);
public:
	ArtisticCommentFactory(logging::Logger& log, cairo::Renderer* renderer, const std::map<std::string, std::string> & config);
	virtual ~ArtisticCommentFactory();
private:
	void setColor(cairo_t* cairo, unsigned int color);
	void setupCairo(std::shared_ptr<saccubus::draw::Context> ctx, cairo_t* cairo, double fontSize);
private:
	saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> renderLine(std::shared_ptr<saccubus::draw::Context> ctx, const std::string& str, bool fitToScreen, unsigned long color, unsigned long shadowColor, double size);
	saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> renderLines(std::shared_ptr<saccubus::draw::Context> ctx, const std::string& str, bool fitToScreen, unsigned long color, unsigned long shadowColor, double size);
public:
	virtual saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> renderCommentText(std::shared_ptr<saccubus::draw::Context> ctx, const saccubus::layer::item::Comment* comment);
	virtual saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> renderLabelText(std::shared_ptr<saccubus::draw::Context> ctx, const saccubus::layer::item::Label* label);
};

}}}
