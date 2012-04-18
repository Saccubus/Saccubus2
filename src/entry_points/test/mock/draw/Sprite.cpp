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
#include "../../../../saccubus/logging/Exception.h"

namespace saccubus {
namespace mock {
namespace draw {

Sprite::Sprite(logging::Logger& log, std::tr1::shared_ptr<saccubus::draw::Renderer*> _renderer, int w, int h)
:saccubus::draw::RawSprite(log, _renderer, w, h)
{

}

Sprite::~Sprite() {
}

void Sprite::draw(std::tr1::shared_ptr<saccubus::draw::Context> _ctx, int x, int y)
{
	Context* const ctx = dynamic_cast<Context*>(_ctx.get());
	ctx->draw(x, y, this);
}

void Sprite::lock(void** data, int* w, int* h, int* stride)
{
	//FIXME
	*data = 0;
	*w = -1;
	*h = -1;
	*stride = -1;
}
void Sprite::unlock()
{

}

}}}
