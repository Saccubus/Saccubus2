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

#include "Context.h"
#include "Renderer.h"
#include "../../logging/Exception.h"
namespace saccubus {
namespace draw {
namespace cairo {

Context::Context(logging::Logger& log, std::tr1::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
:draw::Context(log, renderer)
{
	cairo_format_t cfmt;
	switch(fmt){
	case Renderer::RGB24:
		cfmt = CAIRO_FORMAT_RGB24;
		break;
	case Renderer::ARGB32:
		cfmt = CAIRO_FORMAT_ARGB32;
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon format: %d", fmt);
	}
	this->surface(cairo_image_surface_create_for_data(
			reinterpret_cast<unsigned char*>(data),
			cfmt,
			w,
			h,
			stride
			));
	switch(cairo_surface_status(this->surface())){
	case CAIRO_STATUS_SUCCESS:
		break;
	case CAIRO_STATUS_INVALID_STRIDE:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo surface. Invalid stride: %d != %d", stride, cairo_format_stride_for_width(cfmt, w));
	default:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo surface. Unknwon error.");
	}
	this->cairo(cairo_create(this->surface()));
	switch(cairo_status(this->cairo())){
	case CAIRO_STATUS_SUCCESS:
		break;
	case CAIRO_STATUS_WRITE_ERROR:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo context. Write Error.");
	case CAIRO_STATUS_NO_MEMORY:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo context. No Memory.");
	default:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo context. Unknwon error.");
	}
	if(!this->cairo()){
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo context.");
	}
	cairo_set_operator(this->cairo(), CAIRO_OPERATOR_CLEAR);
	cairo_paint(this->cairo());
	cairo_set_operator(this->cairo(), CAIRO_OPERATOR_OVER);
}

Context::~Context() {
	cairo_destroy(this->cairo());
	cairo_surface_flush(this->surface());
	cairo_surface_destroy(this->surface());
}

float Context::width() const
{
	return cairo_image_surface_get_width(this->surface());
}
float Context::height() const
{
	return cairo_image_surface_get_height(this->surface());
}

}}}
