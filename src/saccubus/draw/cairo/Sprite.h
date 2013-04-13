/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
