/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "LayerdSprite.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

LayerdSprite::LayerdSprite()
:Sprite()
{
}

Sprite::Handler<LayerdSprite> LayerdSprite::newInstance()
{
	return Sprite::Handler<LayerdSprite>(new LayerdSprite());
}

void LayerdSprite::resize(int w, int h)
{
	throw logging::Exception(__FILE__, __LINE__, "[BUG] shrink operation not supported in LayerdSprite");
}

LayerdSprite::~LayerdSprite() {
}

int LayerdSprite::width() const
{
	int w = 0;
	for(std::vector<std::pair<Point, Sprite::Handler<Sprite> > >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		const Sprite::Handler<Sprite> spr = it->second;
		w = std::max(w, spr->width() + pt.x());
	}
	return w;
}
int LayerdSprite::height() const
{
	int h = 0;
	for(std::vector<std::pair<Point, Sprite::Handler<Sprite> > >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		const Sprite::Handler<Sprite> spr = it->second;
		h = std::max(h, spr->height() + pt.y());
	}
	return h;
}

void LayerdSprite::draw(std::shared_ptr<draw::Context> ctx, int x, int y)
{
	for(std::vector<std::pair<Point, Sprite::Handler<Sprite> > >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		Sprite::Handler<Sprite> const spr = it->second;
		spr->draw(ctx, x+pt.x(), y+pt.y());
	}
}

std::size_t LayerdSprite::size()
{
	return sprites.size();
}
void LayerdSprite::addSprite(int x, int y, Sprite::Handler<Sprite> spr)
{
	this->sprites.push_back(std::pair<Point, Sprite::Handler<Sprite> >(Point(x,y), spr));
}

void LayerdSprite::onFree()
{
	delete this;
}

}}
