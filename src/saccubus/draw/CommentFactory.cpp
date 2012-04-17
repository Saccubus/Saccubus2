/*
 * CommentFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "CommentFactory.h"

namespace saccubus {
namespace draw {

CommentFactory::CommentFactory(logging::Logger& log, Renderer* renderer)
:log(log)
{
	this->renderer(renderer);
}

CommentFactory::~CommentFactory() {
}

}}

