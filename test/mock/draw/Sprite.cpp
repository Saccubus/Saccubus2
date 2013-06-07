/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Renderer.h"
#include "Sprite.h"
#include "Context.h"
#include "../../../src/saccubus/logging/Exception.h"

namespace samock {
namespace draw {

Sprite::Sprite(std::shared_ptr<saccubus::draw::Renderer*> _renderer, int w, int h)
:saccubus::draw::RawSprite(_renderer, w, h)
{

}

Sprite::~Sprite() {
}

void Sprite::draw(std::shared_ptr<saccubus::draw::Context> _ctx, int x, int y)
{
	Context* const ctx = dynamic_cast<Context*>(_ctx.get());
	ctx->draw(x, y, this);
}

void Sprite::lock(void** data, int* w, int* h, int* stride)
{
	//FIXME
	*data = 0;
	*w = -1;
	*h = -1;
	*stride = -1;
}
void Sprite::unlock()
{

}

}}
