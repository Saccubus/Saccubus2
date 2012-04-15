/*
 * SimpleCommentFactory.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include "SimpleCommentFactory.h"
#include "Renderer.h"

namespace saccubus {
namespace draw {
namespace sdl {

SimpleCommentFactory::SimpleCommentFactory(sdl::Renderer* renderer)
:CommentFactory(renderer)
{
	// TODO Auto-generated constructor stub

}

SimpleCommentFactory::~SimpleCommentFactory() {
	// TODO Auto-generated destructor stub
}

saccubus::draw::RawSprite::Handler SimpleCommentFactory::renderComment(const saccubus::context::Comment* comment)
{

}

}}}
