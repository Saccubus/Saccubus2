/*
 * RawSprite.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include "RawSprite.h"
#include "Renderer.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

RawSprite::RawSprite(std::tr1::shared_ptr<Renderer*> _renderer)
:Sprite()
,_renderer(_renderer)
{
}
RawSprite::RawSprite(std::tr1::shared_ptr<Renderer*> _renderer, int w, int h)
:Sprite(w, h)
,_renderer(_renderer)
{

}

RawSprite::~RawSprite() {
}

void RawSprite::shrink(int w, int h)
{
	this->width(w);
	this->height(h);
}

void RawSprite::onFree()
{
	if(renderer()){
		renderer()->backRawSprite(this);
	}else{ //親のファクトリが死んでしまったので、自分で後始末しなければならない。
		delete this;
	}
}

//---------------------------------------------------------------------------------------------------------------------
RawSprite::Session::Session(Sprite::Handler<RawSprite> spr)
:sprite(spr)
{
	this->sprite->lock(&_data, &_w, &_h, &_stride);
}
RawSprite::Session::~Session()
{
	this->sprite->unlock();
}
void* RawSprite::Session::data() const
{
	return this->_data;
}
int RawSprite::Session::width() const
{
	return this->_w;
}
int RawSprite::Session::height() const
{
	return this->_h;
}
int RawSprite::Session::stride() const
{
	return this->_stride;
}

}}
