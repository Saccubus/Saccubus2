/*
 * Renderer.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef SDL_RENDERER_H_
#define SDL_RENDERER_H_

#include "../Renderer.h"
#include "../../util/ClassAccessor.h"
#include "../../classdefs.h"

struct SDL_Renderer;
struct SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Window SDL_Window;
namespace saccubus {
namespace draw {
namespace sdl {

class Renderer : public saccubus::draw::Renderer {
private:
	const bool sdlInitializedByMe;
	DEF_ATTR_ACCESSOR(public, private, SDL_Window*, window);
	DEF_ATTR_ACCESSOR(public, private, SDL_Renderer*, renderer);
public:
	Renderer(const int w, const int h);
	virtual ~Renderer();
public:
	void windowVisibility(bool visibility);
	void windowTitle(const std::string& title);
	std::string windowTitle();
	void updateWindow();
protected: /* 各実装がこれを実際に実装する */
	virtual draw::RawSprite* createSprite(int w, int h);
};

}}}
#endif /* SDL_RENDERER_H_ */
