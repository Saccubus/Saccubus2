/*
 * SimpleCommentFactory.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include "SimpleCommentFactory.h"
#include "ImageFactory.h"

namespace saccubus {
namespace draw {
namespace sdl {

SimpleCommentFactory::SimpleCommentFactory(sdl::ImageFactory* imgFactory)
:CommentFactory(imgFactory)
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
