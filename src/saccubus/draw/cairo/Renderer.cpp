/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "Renderer.h"
#include "Sprite.h"
#include "Context.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace cairo {

Renderer::Renderer(cinamo::Logger& log, const std::map<std::string, std::string> & config)
:saccubus::draw::Renderer(log)
{
}

Renderer::~Renderer() {
}

draw::RawSprite* Renderer::createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
{
	return new cairo::Sprite(this->handler(), fmt, data, w, h, stride);
}
draw::RawSprite* Renderer::createRawSprite(int w, int h)
{
	return new cairo::Sprite(this->handler(), w, h);
}
std::shared_ptr<draw::Context> Renderer::createContext(enum Format fmt, void* data, int w, int h, int stride)
{
	return std::shared_ptr<draw::Context>(new Context(log, handler(), fmt, data, w, h, stride));
}

cairo_format_t Renderer::toCairoFormat(draw::Renderer::Format fmt)
{
	cairo_format_t cfmt;
	switch(fmt){
	case Renderer::RGB32:
		cfmt = CAIRO_FORMAT_RGB24;
		break;
	case Renderer::ARGB32:
		cfmt = CAIRO_FORMAT_ARGB32;
		break;
	default:
		cfmt = CAIRO_FORMAT_INVALID;
		break;
	}
	return cfmt;
}

}}}
