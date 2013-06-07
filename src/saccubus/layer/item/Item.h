/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
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
	virtual ~Item() noexcept = default;
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
