/*
 * Sprite.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SDL_SPRITE_H_
#define SDL_SPRITE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "../Sprite.h"
#include "Renderer.h"

namespace saccubus {
namespace draw {
namespace sdl {

class Sprite : public draw::RawSprite {
	DEF_ATTR_ACCESSOR(public, private, SDL_Texture*, texture);
public:
	Sprite(logging::Logger& log, std::tr1::shared_ptr<draw::Renderer*> renderer, int w, int h);
	virtual ~Sprite();
	virtual void draw(draw::Renderer* renderer, int x, int y);
	virtual void lock(void** data, int* w, int* h, int* stride);
	virtual void unlock();
};

}}}

#endif /* SDL_SPRITE_H_ */
