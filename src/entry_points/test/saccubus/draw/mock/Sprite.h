/*
 * Sprite.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef TEST_SPRITE_H_
#define TEST_SPRITE_H_

#include "../../../../../saccubus/draw/RawSprite.h"

namespace saccubus {
namespace test {
namespace draw {

class Sprite: public saccubus::draw::RawSprite {
public:
	Sprite(std::tr1::shared_ptr<saccubus::draw::SpriteFactory*> _factory, int w, int h);
	virtual ~Sprite();
	virtual void draw(saccubus::draw::Canvas* __canvas, int x, int y);
};

}}}
#endif /* TEST_SPRITE_H_ */