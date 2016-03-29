/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "CommentFactory.h"

namespace saccubus {
namespace draw {

CommentFactory::CommentFactory(cinamo::Logger& log, Renderer* renderer)
:log(log)
{
	this->renderer(renderer);
}

CommentFactory::~CommentFactory() {
}

}}

