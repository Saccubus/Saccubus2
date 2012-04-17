/*
 * Sprite.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef MOCK_DRAW_SPRITE_H_
#define MOCK_DRAW_SPRITE_H_

#include "../../../../saccubus/draw/RawSprite.h"

namespace saccubus {
namespace mock {
namespace draw {

class Sprite: public saccubus::draw::RawSprite {
public:
	Sprite(logging::Logger& log, std::tr1::shared_ptr<saccubus::draw::Renderer*> _renderer, int w, int h);
	virtual ~Sprite();
	virtual void draw(saccubus::draw::Renderer* __renderer, int x, int y);
	virtual void lock(void** data, int* w, int* h, int* stride);
	virtual void unlock();
};

}}}
#endif /* MOCK_DRAW_SPRITE_H_ */
