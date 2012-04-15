/*
 * ImageFactory.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef SDL_IMAGEFACTORY_H_
#define SDL_IMAGEFACTORY_H_

#include "../../classdefs.h"
#include "../ImageFactory.h"

namespace saccubus {
namespace draw {
namespace sdl {

class ImageFactory: public saccubus::draw::ImageFactory {
public:
	ImageFactory();
	virtual ~ImageFactory();
protected: /* 各実装がこれを実際に実装する */
	virtual draw::RawSprite* createSprite(int w, int h);
};

}}}
#endif /* SDL_IMAGEFACTORY_H_ */
