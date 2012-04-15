/*
 * Sprite.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "Renderer.h"
#include "Sprite.h"
#include "../../../../saccubus/logging/Exception.h"

namespace saccubus {
namespace mock {
namespace draw {

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

Sprite::Sprite(std::tr1::shared_ptr<saccubus::draw::Renderer*> _renderer, int w, int h)
:saccubus::draw::RawSprite(_renderer, w, h)
{

}
void Sprite::draw(saccubus::draw::Renderer* __renderer, int x, int y)
{
	if(__renderer != this->renderer()){
		logging::Exception(__FILE__, __LINE__, "Sprite renderer and target renderer has been changed!!");
	}
	Renderer& renderer = dynamic_cast<Renderer&>(*__renderer);
	renderer.draw(x, y, this);
}


}}}
