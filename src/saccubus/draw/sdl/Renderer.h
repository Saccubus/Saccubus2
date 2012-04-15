/*
 * Renderer.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef SDL_RENDERER_H_
#define SDL_RENDERER_H_

#include <SDL2/SDL.h>
#include "../Renderer.h"
#include "../../util/ClassAccessor.h"
#include "../../classdefs.h"

namespace saccubus {
namespace draw {
namespace sdl {

class Renderer : public saccubus::draw::Renderer {
	DEF_ATTR_ACCESSOR(public, private, SDL_Renderer*, renderer);
public:
	Renderer();
	virtual ~Renderer();
protected: /* 各実装がこれを実際に実装する */
	virtual draw::RawSprite* createSprite(int w, int h);
};

}}}
#endif /* SDL_RENDERER_H_ */
