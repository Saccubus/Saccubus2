/*
 * Sprite.cpp
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#include "Sprite.h"
#include "../../logging/Exception.h"
#include <SDL2/SDL_rect.h>

namespace saccubus {
namespace draw {
namespace sdl {

Sprite::Sprite(int w, int h, SDL_Texture* texture)
:draw::Sprite(w, h)
{
	this->texture(texture);

}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

void Sprite::draw(draw::Renderer* _renderer, int x, int y)
{
	sdl::Renderer& canvas = dynamic_cast<sdl::Renderer&>(*_renderer);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = this->width();
	dst.h = this->height();
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = this->width();
	src.h = this->height();

	if( SDL_RenderCopy(canvas.renderer(), this->texture(), &src, &dst) != 0)
	{
		throw logging::Exception("Failed to render SDL Sprite!!");
	}
}


}}}
