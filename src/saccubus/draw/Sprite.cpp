/*
 * Sprite.cpp
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#include "Sprite.h"
#include "SpriteFactory.h"
#include "../logging/Exception.h"

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


void Sprite::Handler::incref()
{
	sprite->refcount++;
}
void Sprite::Handler::decref()
{
	sprite->refcount--;
	if(sprite->refcount < 0){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite::Handler cnt = %d < 0", sprite->refcount);
	}else if(sprite->refcount == 0){
		SpriteFactory* factory = *this->factory.get();
		if(factory){
			factory->backSprite(this->sprite);
		}else{ //親のファクトリが死んでしまったので、自分で後始末しなければならない。
			delete this->sprite;
		}
	}

}
Sprite::Handler::Handler(Sprite* const sprite, std::tr1::shared_ptr<SpriteFactory*> factory)
:sprite(sprite), factory(factory)
{
	incref();
}
Sprite::Handler::Handler(const Sprite::Handler& other)
:sprite(other.sprite), factory(other.factory)
{
	if(sprite){
		incref();
	}
}
Sprite::Handler::Handler()
:sprite(0), factory()
{
}

Sprite::Handler& Sprite::Handler::operator=(const Sprite::Handler& other)
{
	if(sprite){
		decref();
	}
	this->sprite = other.sprite;
	this->factory = other.factory;
	if(sprite){
		incref();
	}
	return *this;
}
Sprite::Handler::~Handler()
{
	if(sprite){
		decref();
	}
}
Sprite* Sprite::Handler::operator->() const
{
	return sprite;
}
Sprite* Sprite::Handler::operator*() const
{
	return sprite;
}

Sprite::Handler::operator bool() const
{
	return sprite != 0;
}

}}
