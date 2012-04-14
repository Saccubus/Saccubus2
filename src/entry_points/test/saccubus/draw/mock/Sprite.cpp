/*
 * Sprite.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "Canvas.h"
#include "Sprite.h"

namespace saccubus {
namespace test {
namespace draw {

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

Sprite::Sprite(int w, int h)
:saccubus::draw::Sprite(w, h)
{

}
void Sprite::draw(saccubus::draw::Canvas* __canvas, int x, int y)
{
	Canvas& canvas = dynamic_cast<Canvas&>(*__canvas);
	canvas.draw(x, y, this);
}


}}}
