/*
 * SpriteFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "SpriteFactory.h"
#include "Sprite.h"

namespace saccubus {
namespace test {
namespace draw {

SpriteFactory::SpriteFactory() {
}

SpriteFactory::~SpriteFactory() {
}

saccubus::draw::Sprite* SpriteFactory::createSprite(int w, int h)
{
	return new Sprite(w, h);
}

}}}
