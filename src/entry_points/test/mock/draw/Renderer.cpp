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

namespace saccubus {
namespace mock {
namespace draw {

Renderer::Renderer(logging::Logger& log)
:saccubus::draw::Renderer(log, 640, 480){
}

Renderer::~Renderer() {
}

saccubus::draw::RawSprite* Renderer::createRawSprite(int w, int h)
{
	return new Sprite(log, handler(), w, h);
}

void Renderer::draw(int x, int y, Sprite* spr)
{
	this->drawQuery.push_back(std::pair<std::pair<int,int>,Sprite* >(std::pair<int, int>(x, y), spr));
}

Renderer::QueryIterator Renderer::queryBegin()
{
	return this->drawQuery.begin();
}
Renderer::QueryIterator Renderer::queryEnd()
{
	return this->drawQuery.end();
}
std::size_t Renderer::querySize()
{
	return this->drawQuery.size();
}
}}}
