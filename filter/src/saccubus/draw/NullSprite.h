/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once

#include "Sprite.h"

namespace saccubus {
namespace draw {

class NullSprite: public saccubus::draw::Sprite {
private:
	int _width;
	int _height;
public:
	static Sprite::Handler<Sprite> newInstance(int width, int height);
private:
	NullSprite(int width, int height);
public:
	virtual ~NullSprite();
protected:
	virtual void onFree();
public:
	virtual int width() const;
	virtual int height() const;
	virtual void draw(std::shared_ptr<draw::Context> ctx, int x, int y);
	virtual void resize(int w, int h);
};

}}
