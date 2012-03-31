/*
 * Canvas.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include "../classdefs.h"

namespace saccubus {
namespace draw {

class Canvas {
public:
	Canvas();
	virtual ~Canvas();
public:
	virtual Sprite* querySprite(int w, int h) = 0;
public:
};

}}
#endif /* CANVAS_H_ */