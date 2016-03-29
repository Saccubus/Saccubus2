/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once

#include <vector>
#include "../classdefs.h"
#include "Sprite.h"

namespace saccubus {
namespace draw {

class LayerdSprite: public saccubus::draw::Sprite {
private:
	std::vector<std::pair<Point, Sprite::Handler<Sprite> > > sprites;
private:
	LayerdSprite();
public:
	static Sprite::Handler<LayerdSprite> newInstance();
	virtual ~LayerdSprite();
public:
	virtual void draw(std::shared_ptr<draw::Context> ctx, int x, int y);
	std::size_t size();
	void addSprite(int x, int y, Sprite::Handler<Sprite> spr);
	virtual void onFree();
	virtual void resize(int w, int h);
	virtual int width() const;
	virtual int height() const;
};

}}
