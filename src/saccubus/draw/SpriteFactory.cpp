/*
 * SpriteFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include <algorithm>
#include "SpriteFactory.h"

namespace saccubus {
namespace draw {

SpriteFactory::SpriteFactory()
:_handler(new SpriteFactory*(this))
{

}

SpriteFactory::~SpriteFactory() {
	*(handler().get()) = 0;
}

RawSprite::Handler SpriteFactory::querySprite(int w, int h)
{
	SpriteIterator it = std::lower_bound(unusedSprites.begin(), unusedSprites.end(), std::pair<int, int>(w,h), order());
	if(it == unusedSprites.end()){
		RawSprite::Handler handler(createSprite(w, h));
		return handler;
	}else{
		RawSprite::Handler handler(*it);
		unusedSprites.erase(it);
		handler->shrink(w, h);
		return handler;
	}
}

void SpriteFactory::backSprite(RawSprite* spr)
{
	SpriteIterator it = std::upper_bound(unusedSprites.begin(), unusedSprites.end(), spr, order());
	unusedSprites.insert(it, spr);
}

std::size_t SpriteFactory::availableSprites()
{
	return unusedSprites.size();
}

bool SpriteFactory::order::operator ()(const Sprite* a, const Sprite* b)
{
	return a->width() < b->width() && a->height() < b->height();
}
bool SpriteFactory::order::operator() (const Sprite* a, const std::pair<int,int>& b)
{
	return a->width() < b.first && a->height() < b.second;
}
bool SpriteFactory::order::operator() (const std::pair<int,int>& a, const Sprite* b)
{
	return a.first < b->width() && a.second < b->height();
}


}}

