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

Sprite::Sprite(std::tr1::shared_ptr<draw::Renderer*> renderer, int w, int h)
:draw::RawSprite(renderer, w, h)
{
	sdl::Renderer& _renderer = dynamic_cast<sdl::Renderer&>(*(this->renderer()));
	this->texture(SDL_CreateTexture(_renderer.renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h));

}

Sprite::~Sprite() {
	SDL_DestroyTexture(this->texture());
	this->texture(0);
}

void Sprite::draw(draw::Renderer* __renderer, int x, int y)
{
	if(__renderer != this->renderer()){
		logging::Exception(__FILE__, __LINE__, "Sprite renderer and target renderer has been changed!!");
	}
	sdl::Renderer& _renderer = dynamic_cast<sdl::Renderer&>(*__renderer);
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

	if( SDL_RenderCopy(_renderer.renderer(), this->texture(), &src, &dst) != 0)
	{
		throw logging::Exception("Failed to render SDL Sprite!!");
	}
}
void Sprite::lock(void** data, int* w, int* h, int* stride)
{
	SDL_Rect rect;
	rect.x=0;
	rect.y=0;
	*w = this->width();
	*h = this->height();
	rect.w=*w;
	rect.h=*h;
	SDL_LockTexture(this->texture(), &rect, data, stride);
}
void Sprite::unlock()
{
	SDL_UnlockTexture(this->texture());
}


}}}
