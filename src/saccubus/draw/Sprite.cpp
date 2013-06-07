/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "Sprite.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

Sprite::Sprite()
:refcount(0)
{
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
