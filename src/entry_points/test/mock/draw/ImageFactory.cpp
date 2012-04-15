/*
 * ImageFactory.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "ImageFactory.h"
#include "Sprite.h"

namespace saccubus {
namespace mock {
namespace draw {

ImageFactory::ImageFactory() {
}

ImageFactory::~ImageFactory() {
}

saccubus::draw::RawSprite* ImageFactory::createSprite(int w, int h)
{
	return new Sprite(handler(), w, h);
}

}}}
