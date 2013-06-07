/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include <cairo/cairo.h>
#include "../Context.h"
#include "../Renderer.h"

namespace saccubus {
namespace draw {
namespace cairo {

class Context: public saccubus::draw::Context {
	DEFINE_MEMBER(public, private, cairo_t*, cairo);
	DEFINE_MEMBER(private, private, cairo_surface_t*, surface);
public:
	Context(cinamo::Logger& log, std::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	virtual ~Context();
public:
	virtual float width() const;
	virtual float height() const;
};

}}}
