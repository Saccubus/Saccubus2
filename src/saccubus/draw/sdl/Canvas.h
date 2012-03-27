/*
 * Canvas.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SDL_CANVAS_H_
#define SDL_CANVAS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "../Canvas.h"

namespace saccubus {
namespace draw {
namespace sdl {

class Canvas: public draw::Canvas {
private:
	SDL_Renderer* const renderer;
public:
	Canvas(SDL_Renderer* renderer);
	virtual ~Canvas();
	virtual Sprite* querySprite(int w, int h);
};

}}}
#endif /* SDL_CANVAS_H_ */
