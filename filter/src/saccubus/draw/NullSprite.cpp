/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "NullSprite.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

Sprite::Handler<Sprite> NullSprite::newInstance(int width, int height)
{
	return Sprite::Handler<Sprite>(new NullSprite(width, height));
}

NullSprite::NullSprite(int width, int height)
:Sprite(), _width(width), _height(height)
{
}

NullSprite::~NullSprite() {
}

void NullSprite::onFree()
{
	delete this;
}
int NullSprite::width() const
{
	return _width;
}
int NullSprite::height() const
{
	return _height;
}
void NullSprite::draw(std::shared_ptr<draw::Context> ctx, int x, int y)
{
	//null。なにも描画しない。
}
void NullSprite::resize(int w, int h)
{
	throw logging::Exception(__FILE__, __LINE__, "[BUG] Can't resize NullSprite (0, 0) to (%d,%d)",w,h);
}


}}

