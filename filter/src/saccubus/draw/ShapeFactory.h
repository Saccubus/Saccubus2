/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <nekomata/system/System.h>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include "RawSprite.h"

namespace saccubus {
namespace draw {

class ShapeFactory {
private:
	DEFINE_MEMBER(protected, private, Renderer*, renderer);
protected:
	cinamo::Logger& log;
public:
	ShapeFactory(cinamo::Logger& log, Renderer* renderer);
	virtual ~ShapeFactory();
public:
	virtual Sprite::Handler<Sprite> renderButton(std::shared_ptr<saccubus::draw::Context> ctx, int w, int h, unsigned int color) = 0;
	virtual Sprite::Handler<Sprite> renderShape(std::shared_ptr<saccubus::draw::Context> ctx, const nekomata::system::Shape* const shape) = 0;
};

}}
