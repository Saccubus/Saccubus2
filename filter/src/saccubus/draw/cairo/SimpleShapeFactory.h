/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Logger.h>
#include "Renderer.h"
#include "../ShapeFactory.h"

namespace saccubus {
namespace draw {
namespace cairo {

class SimpleShapeFactory: public saccubus::draw::ShapeFactory {
public:
	SimpleShapeFactory(cinamo::Logger& log, cairo::Renderer* renderer, const std::map<std::string, std::string> & config);
	virtual ~SimpleShapeFactory();
public:
	virtual Sprite::Handler<draw::Sprite> renderButton(std::shared_ptr<saccubus::draw::Context> ctx, int w, int h, unsigned int color);
	virtual Sprite::Handler<draw::Sprite> renderShape(std::shared_ptr<saccubus::draw::Context> ctx, const nekomata::system::Shape* const shape);
};

}}}
