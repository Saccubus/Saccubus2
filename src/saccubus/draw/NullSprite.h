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

#ifndef Saccubus_NULLSPRITE_H__CPP_
#define Saccubus_NULLSPRITE_H__CPP_

#include "Sprite.h"

namespace saccubus {
namespace draw {

class NullSprite: public saccubus::draw::Sprite {
public:
	static Sprite::Handler<Sprite> newInstance();
private:
	NullSprite();
public:
	virtual ~NullSprite();
protected:
	virtual void onFree();
public:
	virtual int width() const;
	virtual int height() const;
	virtual void draw(std::tr1::shared_ptr<draw::Context> ctx, int x, int y);
	virtual void resize(int w, int h);
};

}}
#endif /* INCLUDE_GUARD */
