/*
 * LayerdSprite.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
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

void LayerdSprite::shrink(int w, int h)
{
	throw logging::Exception(__FILE__, __LINE__, "[BUG] shrink operation not supported in LayerdSprite");
}

LayerdSprite::~LayerdSprite() {
}

void LayerdSprite::updateSize()
{
	int w = 0;
	int h = 0;
	for(std::vector<std::pair<Point, Sprite::Handler<Sprite> > >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		const Sprite::Handler<Sprite> spr = it->second;
		w = std::max(w, spr->width() + pt.x());
		h = std::max(h, spr->height() + pt.y());
	}
	this->width(w);
	this->height(h);
}

void LayerdSprite::draw(Renderer* renderer, int x, int y)
{
	for(std::vector<std::pair<Point, Sprite::Handler<Sprite> > >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		Sprite::Handler<Sprite> const spr = it->second;
		spr->draw(renderer, x+pt.x(), y+pt.y());
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
