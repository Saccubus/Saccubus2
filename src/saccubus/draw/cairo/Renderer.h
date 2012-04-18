/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CAIRO_RENDERER_H_
#define CAIRO_RENDERER_H_

#include "../Renderer.h"
#include "../../util/ClassAccessor.h"
#include "../../classdefs.h"

struct SDL_Renderer;
struct SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Window SDL_Window;
namespace saccubus {
namespace draw {
namespace cairo {

class Renderer : public saccubus::draw::Renderer {
private:
	const bool sdlInitializedByMe;
	DEF_ATTR_ACCESSOR(public, private, SDL_Window*, window);
	DEF_ATTR_ACCESSOR(public, private, SDL_Renderer*, renderer);
public:
	Renderer(logging::Logger& log, const int w, const int h);
	virtual ~Renderer();
public:
	void windowVisibility(bool visibility);
	void windowTitle(const std::string& title);
	std::string windowTitle();
	void updateWindow();
protected: /* 各実装がこれを実際に実装する */
	virtual draw::RawSprite* createRawSprite(int w, int h);
};

}}}
#endif /* INCLUDE_GUARD */
