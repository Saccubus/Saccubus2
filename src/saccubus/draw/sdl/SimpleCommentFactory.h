/*
 * SimpleCommentFactory.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef SDL_SIMPLECOMMENTFACTORY_H_
#define SDL_SIMPLECOMMENTFACTORY_H_

#include <cairo/cairo-ft.h>
#include <fontconfig/fontconfig.h>
#include "../../classdefs.h"
#include "../CommentFactory.h"

namespace saccubus {
namespace draw {
namespace sdl {

class Renderer;
class SimpleCommentFactory: public saccubus::draw::CommentFactory {
private:
	static const double ShadowWidth;
private:
	DEF_ATTR_ACCESSOR(private, private, FcPattern*, pattern);
	DEF_ATTR_ACCESSOR(private, private, cairo_font_face_t*, face);
	DEF_ATTR_ACCESSOR(private, private, cairo_t*, emptyCairo);
	DEF_ATTR_ACCESSOR(private, private, cairo_surface_t*, emptySurface);
public:
	SimpleCommentFactory(sdl::Renderer* renderer);
	virtual ~SimpleCommentFactory();
private:
	void setFont(cairo_t* cairo, const saccubus::context::Comment* comment);
	void setColor(cairo_t* cairo, unsigned int color);
public:
	virtual saccubus::draw::RawSprite::Handler renderComment(const saccubus::context::Comment* comment);
};

}}}
#endif /* SDL_SIMPLECOMMENTFACTORY_H_ */
