/*
 * Sprite.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "Canvas.h"
#include "Sprite.h"

namespace saccubus {
namespace mock {
namespace draw {

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

Sprite::Sprite(std::tr1::shared_ptr<saccubus::draw::ImageFactory*> _factory, int w, int h)
:saccubus::draw::RawSprite(_factory, w, h)
{

}
void Sprite::draw(saccubus::draw::Canvas* __canvas, int x, int y)
{
	Canvas& canvas = dynamic_cast<Canvas&>(*__canvas);
	canvas.draw(x, y, this);
}


}}}
