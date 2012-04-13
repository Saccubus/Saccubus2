/*
 * Sprite.cpp
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#include "Sprite.h"

namespace saccubus {
namespace draw {

Sprite::Sprite()
{
	this->width(-1);
	this->height(-1);
}

Sprite::Sprite(int w, int h) {
	this->width(w);
	this->height(h);
	// TODO Auto-generated constructor stub

}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

}}
