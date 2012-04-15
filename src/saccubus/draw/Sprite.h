/*
 * Sprite.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <tr1/memory>
#include "../classdefs.h"
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace draw {

class Point{
	DEF_ATTR_ACCESSOR(public, public, int, x);
	DEF_ATTR_ACCESSOR(public, public, int, y);
public:
	Point(int x, int y){this->x(x);this->y(y);};
	Point(const Point& other){this->x(other.x());this->y(other.y());};
	~Point(){};
};

class Sprite {
	DEF_ATTR_ACCESSOR(public, protected, int, width);
	DEF_ATTR_ACCESSOR(public, protected, int, height);
protected:
	Sprite();
	Sprite(int w, int h);
public:
	virtual ~Sprite();
public:
	virtual void draw(Renderer* renderer, int x, int y) = 0;
	virtual void shrink(int w, int h) = 0;
};

}}

#endif /* SPRITE_H_ */
