/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Item.h"

namespace saccubus {
namespace layer {
namespace item {

Item::Item()
{
}

Item::Item(const Item& other)
{

}
Item& Item::operator = (const Item& other)
{
	return *this;
}

void Item::draw(std::shared_ptr<saccubus::draw::Context> ctx, int x, int y)
{
	querySprite(ctx)->draw(ctx, x, y);
}
float Item::width(std::shared_ptr<saccubus::draw::Context> ctx)
{
	return querySprite(ctx)->width();
}
float Item::height(std::shared_ptr<saccubus::draw::Context> ctx)
{
	return querySprite(ctx)->height();
}

draw::Sprite::Handler<draw::Sprite> Item::querySprite(std::shared_ptr<saccubus::draw::Context> ctx)
{
	if(!sprite){
		sprite = this->createSprite(ctx);
	}
	return sprite;
}
void Item::invalidate()
{
	sprite.reset();
}

bool Item::onClick(int relX, int relY)
{
	return false;
}

}}}
