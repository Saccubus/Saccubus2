/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <map>
#include <cairo/cairo.h>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include "../Renderer.h"
#include "../../classdefs.h"

namespace saccubus {
namespace draw {
namespace cairo {

class Renderer : public saccubus::draw::Renderer {
	DEFINE_MEMBER(public, private, cairo_t*, cairo);
public:
	Renderer(cinamo::Logger& log, const std::map<std::string, std::string> & config);
	virtual ~Renderer();
public:
	static cairo_format_t toCairoFormat(draw::Renderer::Format fmt);
public: /* 各実装がこれを実際に実装する */
	virtual std::shared_ptr<saccubus::draw::Context> createContext(enum Format fmt, void* data, int w, int h, int stride);
	virtual draw::RawSprite* createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride);
	virtual draw::RawSprite* createRawSprite(int w, int h);
};

}}}
