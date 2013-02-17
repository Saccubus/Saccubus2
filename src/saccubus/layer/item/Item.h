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
#include "../../draw/Sprite.h"

namespace saccubus {
namespace layer {
namespace item {

class Item {
protected:
	Item();
	Item(const Item& other);
	Item& operator = (const Item& other);
public:
	virtual ~Item();
private:
	draw::Sprite::Handler<draw::Sprite> sprite;
private:
	draw::Sprite::Handler<draw::Sprite> querySprite(std::shared_ptr<saccubus::draw::Context> ctx);
public:
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, int x, int y);
	virtual float width(std::shared_ptr<saccubus::draw::Context> ctx);
	virtual float height(std::shared_ptr<saccubus::draw::Context> ctx);
protected:
	void invalidate();
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::shared_ptr<saccubus::draw::Context> ctx) = 0;
public:
	// イベントが消費される場合はtrue、下レイヤのボタンにイベントが透過する場合はfalseを返す。
	virtual bool onClick(int relX, int relY);
};

}}}
