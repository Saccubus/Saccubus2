/*
 * Renderer.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Sprite.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace sdl {

Renderer::Renderer(const int w, const int h)
:saccubus::draw::Renderer(w, h)
,sdlInitializedByMe(!SDL_WasInit(SDL_INIT_VIDEO))
{
	if (sdlInitializedByMe && SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		throw saccubus::logging::Exception("Failed to initialize SDL: %s",
				SDL_GetError());
	}
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_HIDDEN, &window, &renderer) < 0) {
		if(sdlInitializedByMe){
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
		}
		throw saccubus::logging::Exception(
				"Failed to create window and renderer: %s", SDL_GetError());
	}
	this->window(window);
	this->renderer(renderer);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(this->renderer());
	SDL_DestroyWindow(this->window());
	this->renderer(0);
	if(sdlInitializedByMe){
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
}

draw::RawSprite* Renderer::createRawSprite(int w, int h)
{
	return new sdl::Sprite(this->handler(), w, h);
}

void Renderer::windowVisibility(bool visibility)
{
	if(visibility){
		SDL_ShowWindow(this->window());
	}else{
		SDL_HideWindow(this->window());
	}
}
void Renderer::windowTitle(const std::string& title)
{
	SDL_SetWindowTitle(this->window(), title.c_str());
}
std::string Renderer::windowTitle()
{
	return std::string(SDL_GetWindowTitle(this->window()));
}
void Renderer::updateWindow()
{
	SDL_UpdateWindowSurface(this->window());
}


}}}
