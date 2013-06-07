/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "RawSprite.h"
#include "Renderer.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

RawSprite::RawSprite(std::shared_ptr<Renderer*> _renderer, int w, int h)
:Sprite()
,_renderer(_renderer)
,_locked(false)
{
	this->width(w);
	this->_origWidth=w;
	this->height(h);
	this->_origHeight=h;
}
int RawSprite::width() const
{
	return this->_width;
}
int RawSprite::height() const
{
	return this->_height;
}int RawSprite::origWidth() const
{
	return this->_origWidth;
}
int RawSprite::origHeight() const
{
	return this->_origHeight;
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

void RawSprite::resize(int w, int h)
{
	if(w > this->_origWidth || h > this->_origHeight){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] You can't resize sprite bigger than original.");
	}
	this->width(w);
	this->height(h);
}

void RawSprite::onFree()
{
	if(renderer()){
		this->resize(this->origWidth(), this->origHeight());
		renderer()->backRawSprite(this);
	}else{ //親のファクトリが死んでしまったので、自分で後始末しなければならない。
		delete this;
	}
}

//---------------------------------------------------------------------------------------------------------------------
RawSprite::Session::Session(Sprite::Handler<RawSprite> spr)
:sprite(spr)
{
	if(this->sprite->_locked){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite already locked.");
	}
	this->sprite->_locked = true;
	this->sprite->lock(&_data, &_w, &_h, &_stride);
}
RawSprite::Session::~Session()
{
	this->sprite->unlock();
	this->sprite->_locked = false;
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
