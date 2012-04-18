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

#include "Context.h"

namespace saccubus {
namespace mock {
namespace draw {

Context::Context(logging::Logger& log, std::tr1::shared_ptr<saccubus::draw::Renderer*> renderer)
:saccubus::draw::Context(log, renderer)
{
}

Context::~Context() {
}

void Context::draw(int x, int y, Sprite* spr)
{
	this->drawQuery.push_back(std::pair<std::pair<int,int>,Sprite* >(std::pair<int, int>(x, y), spr));
}

Context::QueryIterator Context::queryBegin()
{
	return this->drawQuery.begin();
}
Context::QueryIterator Context::queryEnd()
{
	return this->drawQuery.end();
}
std::size_t Context::querySize()
{
	return this->drawQuery.size();
}

float Context::width() const
{
	return 640;
}
float Context::height() const
{
	return 480;
}


}}}
