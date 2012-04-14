/*
 * SpriteFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "SpriteFactory.h"

namespace saccubus {
namespace draw {

SpriteFactory::SpriteFactory()
:handler(new SpriteFactory*(this))
{

}

SpriteFactory::~SpriteFactory() {
	*handler.get() = 0;
}

Sprite::Handler SpriteFactory::querySprite(int w, int h)
{
	SpriteIterator it = unusedSprites.lower_bound(std::pair<int, int>(w,h));
	if(it == unusedSprites.end()){
		Sprite::Handler handler(createSprite(w, h), this->handler);
		return handler;
	}else{
		Sprite::Handler handler(it->second, this->handler);
		unusedSprites.erase(it);
		return handler;
	}
}

void SpriteFactory::backSprite(Sprite* spr)
{
	unusedSprites.insert(std::pair<std::pair<int, int>, Sprite*>(std::pair<int,int>(spr->width(), spr->height()), spr));
}

std::size_t SpriteFactory::availableSprites()
{
	return unusedSprites.size();
}

bool SpriteFactory::order::operator ()(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	return a.first < b.first && a.second < b.second;
}


}}

