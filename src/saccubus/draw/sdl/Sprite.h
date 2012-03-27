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
#include "Canvas.h"

namespace saccubus {
namespace draw {
namespace sdl {

class Sprite : public draw::Sprite {
private:
	SDL_Texture* texture;
public:
	Sprite(sdl::Canvas* canvas, int w, int h, SDL_Texture* texture);
	virtual ~Sprite();
};

}}}

#endif /* SDL_SPRITE_H_ */
