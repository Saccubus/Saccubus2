/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "Context.h"
#include "Renderer.h"
#include "../../logging/Exception.h"
namespace saccubus {
namespace draw {
namespace cairo {

Context::Context(cinamo::Logger& log, std::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
:draw::Context(log, renderer)
{
	cairo_format_t cfmt = cairo::Renderer::toCairoFormat(fmt);
	if(cfmt == CAIRO_FORMAT_INVALID){
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
