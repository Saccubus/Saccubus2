/*
 * Sprite.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "../classdefs.h"
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace draw {

class Sprite {
	DEF_ATTR_ACCESSOR(protected, private, Canvas*, canvas);
	DEF_ATTR_ACCESSOR(public, private, int, width);
	DEF_ATTR_ACCESSOR(public, private, int, height);
public:
	Sprite(Canvas* canvas, int w, int h);
	virtual ~Sprite();
	virtual void draw(int x, int y) = 0;
};

}}

#endif /* SPRITE_H_ */
