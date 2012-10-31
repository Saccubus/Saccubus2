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
#include <map>
#include <cairo/cairo.h>
#include "../Renderer.h"
#include "../../util/ClassAccessor.h"
#include "../../classdefs.h"

namespace saccubus {
namespace draw {
namespace cairo {

class Renderer : public saccubus::draw::Renderer {
	DEF_ATTR_ACCESSOR(public, private, cairo_t*, cairo);
public:
	Renderer(logging::Logger& log, const std::map<std::string, std::string> & config);
	virtual ~Renderer();
public:
	static cairo_format_t toCairoFormat(draw::Renderer::Format fmt);
public: /* 各実装がこれを実際に実装する */
	virtual std::tr1::shared_ptr<saccubus::draw::Context> createContext(enum Format fmt, void* data, int w, int h, int stride);
	virtual draw::RawSprite* createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	virtual draw::RawSprite* createRawSprite(int w, int h);
};

}}}
