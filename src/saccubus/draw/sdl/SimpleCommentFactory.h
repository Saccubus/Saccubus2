/*
 * SimpleCommentFactory.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef SDL_SIMPLECOMMENTFACTORY_H_
#define SDL_SIMPLECOMMENTFACTORY_H_

#include "../../classdefs.h"
#include "../CommentFactory.h"

namespace saccubus {
namespace draw {
namespace sdl {

class Renderer;
class SimpleCommentFactory: public saccubus::draw::CommentFactory {
public:
	SimpleCommentFactory(sdl::Renderer* renderer);
	virtual ~SimpleCommentFactory();
public:
	virtual saccubus::draw::RawSprite::Handler renderComment(const saccubus::context::Comment* comment);
};

}}}
#endif /* SDL_SIMPLECOMMENTFACTORY_H_ */
