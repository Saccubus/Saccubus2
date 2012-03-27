/*
 * Canvas.cpp
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#include "Canvas.h"

namespace saccubus {
namespace draw {
namespace sdl {

Canvas::Canvas(SDL_Renderer* renderer)
:renderer(renderer)
{
	// TODO Auto-generated constructor stub

}

Canvas::~Canvas() {
	SDL_DestroyRenderer(renderer);
}

Sprite* Canvas::querySprite(int w, int h)
{
	return 0;
}


}}}
