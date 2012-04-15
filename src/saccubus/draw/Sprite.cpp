/*
 * Sprite.cpp
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#include "Sprite.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

Sprite::Sprite()
:refcount(0)
{
	this->width(-1);
	this->height(-1);
}

Sprite::Sprite(int w, int h)
:refcount(0)
{
	this->width(w);
	this->height(h);
}

Sprite::~Sprite() {
}

void Sprite::incref()
{
	this->refcount++;
}
void Sprite::decref()
{
	this->refcount--;
	if(this->refcount < 0){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] RawSprite::Handler refcount = %d < 0", this->refcount);
	}else if(this->refcount == 0){
		this->onFree();
	}
}

}}
