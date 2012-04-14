/*
 * Sprite.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef TEST_SPRITE_H_
#define TEST_SPRITE_H_

#include "../../../../../saccubus/draw/Sprite.h"

namespace saccubus {
namespace test {
namespace draw {

class Sprite: public saccubus::draw::Sprite {
public:
	Sprite(int w, int h);
	virtual ~Sprite();
	virtual void draw(saccubus::draw::Canvas* __canvas, int x, int y);
};

}}}
#endif /* TEST_SPRITE_H_ */
