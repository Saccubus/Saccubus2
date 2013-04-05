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
#include <cinamo/Logger.h>
#include <cairo/cairo.h>
#include "../Context.h"
#include "../Renderer.h"
#include "../../util/ClassAccessor.h"

namespace saccubus {
namespace draw {
namespace cairo {

class Context: public saccubus::draw::Context {
	DEF_ATTR_ACCESSOR(public, private, cairo_t*, cairo);
	DEF_ATTR_ACCESSOR(private, private, cairo_surface_t*, surface);
public:
	Context(cinamo::Logger& log, std::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	virtual ~Context();
public:
	virtual float width() const;
	virtual float height() const;
};

}}}
