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

RawSprite::RawSprite(std::tr1::shared_ptr<Renderer*> _renderer, int w, int h)
:Sprite()
,_renderer(_renderer)
{
	this->width(w);
	this->height(h);
}
int RawSprite::width() const
{
	return this->_width;
}
int RawSprite::height() const
{
	return this->_height;
}

void RawSprite::width(int val)
{
	this->_width = val;
}
void RawSprite::height(int val)
{
	this->_height = val;
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
