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

#include "Sprite.h"
#include "Context.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace cairo {

Sprite::Sprite(std::tr1::shared_ptr<draw::Renderer*> renderer, int w, int h)
:draw::RawSprite(renderer, w, h)
{
	this->surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h));
}

Sprite::Sprite(std::tr1::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
:draw::RawSprite(renderer, w, h)
{
	cairo_format_t cfmt = cairo::Renderer::toCairoFormat(fmt);
	if(cfmt == CAIRO_FORMAT_INVALID){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon format: %d", fmt);
	}
	this->surface(cairo_image_surface_create_for_data(reinterpret_cast<unsigned char*>(data), cfmt, w, h, stride));
	switch(cairo_surface_status(this->surface())){
	case CAIRO_STATUS_SUCCESS:
		break;
	case CAIRO_STATUS_INVALID_STRIDE:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo surface. Invalid stride: %d != %d", stride, cairo_format_stride_for_width(cfmt, w));
	default:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo surface. Unknwon error.");
	}
}
Sprite::~Sprite() {
	cairo_surface_destroy(this->surface());
	this->surface(0);
}

void Sprite::draw(std::tr1::shared_ptr<saccubus::draw::Context> _ctx, int x, int y)
{
	cairo::Context& ctx = dynamic_cast<cairo::Context&>(*(_ctx.get()));
	cairo_set_source_surface(ctx.cairo(), this->surface(), x, y);
	cairo_rectangle(ctx.cairo(), x, y, this->width(), this->height());
	cairo_clip(ctx.cairo());
	cairo_paint(ctx.cairo());
	cairo_reset_clip(ctx.cairo());
}
void Sprite::lock(void** data, int* w, int* h, int* stride)
{
	cairo_surface_flush(this->surface());
	*w = this->width();
	*h = this->height();
	*stride = cairo_image_surface_get_stride(this->surface());
	*data = cairo_image_surface_get_data(this->surface());
}
void Sprite::unlock()
{
	cairo_surface_mark_dirty_rectangle(this->surface(), 0, 0, this->width(), this->height());
}


}}}
