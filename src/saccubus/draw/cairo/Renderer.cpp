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

#include "Renderer.h"
#include "Sprite.h"
#include "Context.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace cairo {

Renderer::Renderer(logging::Logger& log)
:saccubus::draw::Renderer(log)
{
}

Renderer::~Renderer() {
}

draw::RawSprite* Renderer::createRawSprite(int w, int h)
{
	return new cairo::Sprite(log, this->handler(), w, h);
}

std::tr1::shared_ptr<draw::Context> Renderer::createContext(enum Format fmt, void* data, int w, int h, int stride)
{
	return std::tr1::shared_ptr<draw::Context>(new Context(log, handler(), fmt, data, w, h, stride));
}


}}}
