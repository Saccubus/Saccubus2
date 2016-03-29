/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cairo/cairo.h>
#include "../Sprite.h"
#include "Renderer.h"

namespace saccubus {
namespace draw {
namespace cairo {

class Sprite : public draw::RawSprite {
	DEFINE_MEMBER(public, private, cairo_surface_t*, surface);
public:
	Sprite(std::shared_ptr<draw::Renderer*> renderer, int w, int h);
	Sprite(std::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	virtual ~Sprite();
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, int x, int y);
	virtual void lock(void** data, int* w, int* h, int* stride);
	virtual void unlock();
};

}}}
