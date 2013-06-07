/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once

#include <cinamo/Platform.h>

#include <map>
#if CINAMO_WINDOWS
#include <cairo/cairo-win32.h>
#else
#include <cairo/cairo-ft.h>
#endif
#include <fontconfig/fontconfig.h>
#include <cinamo/Logger.h>
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
#if !(CINAMO_WINDOWS)
	DEFINE_MEMBER(private, private, FcPattern*, pattern);
#endif
	DEFINE_MEMBER(private, private, cairo_font_face_t*, face);
	DEFINE_MEMBER(private, private, cairo_t*, emptyCairo);
	DEFINE_MEMBER(private, private, cairo_surface_t*, emptySurface);
public:
	ArtisticCommentFactory(cinamo::Logger& log, cairo::Renderer* renderer, const std::map<std::string, std::string> & config);
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
