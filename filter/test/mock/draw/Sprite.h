/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include "../../../src/saccubus/draw/RawSprite.h"

namespace samock {
namespace draw {

class Sprite: public saccubus::draw::RawSprite {
public:
	Sprite(std::shared_ptr<saccubus::draw::Renderer*> _renderer, int w, int h);
	virtual ~Sprite();
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, int x, int y);
	virtual void lock(void** data, int* w, int* h, int* stride);
	virtual void unlock();
};

}}
