/*
 * RawSprite.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include "RawSprite.h"
#include "ImageFactory.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

RawSprite::RawSprite(std::tr1::shared_ptr<ImageFactory*> _factory)
:Sprite()
,refcount(0)
,_factory(_factory)
{
}
RawSprite::RawSprite(std::tr1::shared_ptr<ImageFactory*> _factory, int w, int h)
:Sprite(w, h)
,refcount(0)
,_factory(_factory)
{

}

RawSprite::~RawSprite() {
	// TODO Auto-generated destructor stub
}

void RawSprite::shrink(int w, int h)
{
	this->width(w);
	this->height(h);
}

void RawSprite::incref()
{
	this->refcount++;
}
void RawSprite::decref()
{
	this->refcount--;
	if(this->refcount < 0){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] RawSprite::Handler refcount = %d < 0", this->refcount);
	}else if(this->refcount == 0){
		if(factory()){
			factory()->backSprite(this);
		}else{ //親のファクトリが死んでしまったので、自分で後始末しなければならない。
			delete this;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------
RawSprite::Handler::Handler(RawSprite* const sprite)
:sprite(sprite)
{
	if(this->sprite){
		if(this->sprite->refcount != 0){
			throw logging::Exception(__FILE__, __LINE__, "[BUG] RawSprite::Handler created, but refcount = %d, not zero.", this->sprite->refcount);
		}
		this->sprite->incref();
	}
}
RawSprite::Handler::Handler(const RawSprite::Handler& other)
:sprite(other.sprite)
{
	if(this->sprite){
		this->sprite->incref();
	}
}
RawSprite::Handler::Handler()
:sprite(0)
{
}

RawSprite::Handler& RawSprite::Handler::operator=(const RawSprite::Handler& other)
{
	if(this->sprite){
		this->sprite->decref();
	}
	this->sprite = other.sprite;
	if(this->sprite){
		this->sprite->incref();
	}
	return *this;
}
RawSprite::Handler::~Handler()
{
	if(this->sprite){
		this->sprite->decref();
	}
}
RawSprite* RawSprite::Handler::operator->() const
{
	return this->sprite;
}
RawSprite* RawSprite::Handler::operator*() const
{
	return this->sprite;
}

RawSprite::Handler::operator bool() const
{
	return this->sprite != 0;
}

}}
