/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Renderer.h"
#include "Sprite.h"
#include "Context.h"

namespace samock {
namespace draw {

Renderer::Renderer(cinamo::Logger& log)
:saccubus::draw::Renderer(log){
}

Renderer::~Renderer() {
}

saccubus::draw::RawSprite* Renderer::createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
{
	return new Sprite(handler(), w, h);
}
saccubus::draw::RawSprite* Renderer::createRawSprite(int w, int h)
{
	return new Sprite(handler(), w, h);
}

std::shared_ptr<saccubus::draw::Context> Renderer::createContext(enum Format fmt, void* data, int w, int h, int stride)
{
	return std::shared_ptr<saccubus::draw::Context>(new Context(this->log, handler()));
}
std::shared_ptr<saccubus::draw::Context> Renderer::createContext()
{
	return std::shared_ptr<saccubus::draw::Context>(new Context(this->log, handler()));
}

}}
