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

#include "NullSprite.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

Sprite::Handler<Sprite> NullSprite::newInstance(logging::Logger& log)
{
	return Sprite::Handler<Sprite>(new NullSprite(log));
}

NullSprite::NullSprite(logging::Logger& log)
:Sprite(log)
{
}

NullSprite::~NullSprite() {
}

void NullSprite::onFree()
{
	delete this;
}
int NullSprite::width() const
{
	return 0;
}
int NullSprite::height() const
{
	return 0;
}
void NullSprite::draw(std::tr1::shared_ptr<draw::Context> ctx, int x, int y)
{
	//null。なにも描画しない。
}
void NullSprite::resize(int w, int h)
{
	throw logging::Exception(__FILE__, __LINE__, "[BUG] Can't resize NullSprite (0, 0) to (%d,%d)",w,h);
}


}}

