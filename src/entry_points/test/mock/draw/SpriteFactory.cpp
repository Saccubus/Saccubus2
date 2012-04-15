/*
 * SpriteFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "SpriteFactory.h"
#include "Sprite.h"

namespace saccubus {
namespace mock {
namespace draw {

SpriteFactory::SpriteFactory() {
}

SpriteFactory::~SpriteFactory() {
}

saccubus::draw::RawSprite* SpriteFactory::createSprite(int w, int h)
{
	return new Sprite(handler(), w, h);
}

}}}
