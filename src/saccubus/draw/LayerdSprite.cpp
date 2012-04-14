/*
 * LayerdSprite.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#include "LayerdSprite.h"

namespace saccubus {
namespace draw {

LayerdSprite::LayerdSprite()
:Sprite()
{
	// TODO Auto-generated constructor stub

}

LayerdSprite::~LayerdSprite() {
	// TODO Auto-generated destructor stub
}

void LayerdSprite::updateSize()
{
	int w = 0;
	int h = 0;
	for(std::vector<std::pair<Point, Sprite*> >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		const Sprite* const spr = it->second;
		w = std::max(w, spr->width() + pt.x());
		h = std::max(h, spr->height() + pt.y());
	}
	this->width(w);
	this->height(h);
}

void LayerdSprite::draw(Canvas* canvas, int x, int y)
{
	for(std::vector<std::pair<Point, Sprite*> >::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		const Point pt = it->first;
		Sprite* const spr = it->second;
		spr->draw(canvas, x+pt.x(), y+pt.y());
	}
}

std::size_t LayerdSprite::size()
{
	return sprites.size();
}
void LayerdSprite::addSprite(int x, int y, Sprite* spr)
{
	this->sprites.push_back(std::pair<Point, Sprite*>(Point(x,y), spr));
}
}}
