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

class Point{
	DEF_ATTR_ACCESSOR(public, public, int, x);
	DEF_ATTR_ACCESSOR(public, public, int, y);
public:
	Point(int x, int y);
	Point(const Point& other){x(other.x());y(other.y());};
	~Point(){};
};

class Sprite {
	DEF_ATTR_ACCESSOR(public, protected, int, width);
	DEF_ATTR_ACCESSOR(public, protected, int, height);
protected:
	Sprite();
public:
	Sprite(int w, int h);
	virtual ~Sprite();
	virtual void draw(Canvas* canvas, int x, int y) = 0;
};

}}

#endif /* SPRITE_H_ */
