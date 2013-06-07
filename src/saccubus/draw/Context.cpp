/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "Context.h"

namespace saccubus {
namespace draw {

Context::Context(cinamo::Logger& log, std::shared_ptr<Renderer*> renderer)
:_renderer(renderer)
,log(log)
{
}

Renderer* Context::renderer()
{
	return *(_renderer.get());
}

Context::~Context() {
}

}}
