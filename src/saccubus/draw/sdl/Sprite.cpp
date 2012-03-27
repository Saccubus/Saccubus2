/*
 * Sprite.cpp
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#include "Sprite.h"

namespace saccubus {
namespace draw {
namespace sdl {

Sprite::Sprite(sdl::Canvas* canvas, int w, int h, SDL_Texture* texture)
:draw::Sprite(canvas, w, h)
,texture(texture)
{
	// TODO Auto-generated constructor stub

}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

}}}
