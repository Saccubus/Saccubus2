/*
 * Renderer.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include <SDL2/SDL.h>
#include "Renderer.h"

namespace saccubus {
namespace draw {
namespace sdl {

Renderer::Renderer() {
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(this->renderer());
	this->renderer(0);
}

draw::RawSprite* Renderer::createSprite(int w, int h)
{
}


}}}
