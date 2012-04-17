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

#ifndef DRAW_LAYERDSPRITE_H_
#define DRAW_LAYERDSPRITE_H_

#include <vector>
#include "../classdefs.h"
#include "Sprite.h"

namespace saccubus {
namespace draw {

class LayerdSprite: public saccubus::draw::Sprite {
private:
	std::vector<std::pair<Point, Sprite::Handler<Sprite> > > sprites;
private:
	LayerdSprite(logging::Logger& log);
public:
	static Sprite::Handler<LayerdSprite> newInstance(logging::Logger& log);
	virtual ~LayerdSprite();
public:
	virtual void draw(Renderer* renderer, int x, int y);
	std::size_t size();
	void addSprite(int x, int y, Sprite::Handler<Sprite> spr);
	virtual void onFree();
	virtual void resize(int w, int h);
	virtual int width() const;
	virtual int height() const;
};

}}
#endif /* DRAW_LAYERDSPRITE_H_ */
