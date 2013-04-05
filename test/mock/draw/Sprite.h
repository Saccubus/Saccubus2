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
#include "../../../src/saccubus/draw/RawSprite.h"

namespace saccubus {
namespace mock {
namespace draw {

class Sprite: public saccubus::draw::RawSprite {
public:
	Sprite(std::shared_ptr<saccubus::draw::Renderer*> _renderer, int w, int h);
	virtual ~Sprite();
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, int x, int y);
	virtual void lock(void** data, int* w, int* h, int* stride);
	virtual void unlock();
};

}}}