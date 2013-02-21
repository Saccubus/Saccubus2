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

#include <vector>
#include "Sprite.h"
#include "../../../src/saccubus/classdefs.h"
#include "../../../src/saccubus/draw/Context.h"

namespace saccubus {
namespace mock {
namespace draw {

class Context: public saccubus::draw::Context {
public:
	Context(logging::Logger& log, std::shared_ptr<saccubus::draw::Renderer*> renderer);
	virtual ~Context();
private:
	std::vector<std::pair<std::pair<int, int>, Sprite* > > drawQuery;
public:
	typedef std::vector<std::pair<std::pair<int, int>, Sprite* > >::const_iterator QueryIterator;
public:
	virtual void draw(int x, int y, Sprite* spr);
	QueryIterator queryBegin();
	QueryIterator queryEnd();
	std::size_t querySize();
public:
	virtual float width() const;
	virtual float height() const;

};

}}}
