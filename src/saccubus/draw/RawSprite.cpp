/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RawSprite.h"
#include "Renderer.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

RawSprite::RawSprite(std::tr1::shared_ptr<Renderer*> _renderer, int w, int h)
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
