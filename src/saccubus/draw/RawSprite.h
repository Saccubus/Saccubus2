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
#pragma once

#include "Sprite.h"

namespace saccubus {
namespace draw {
/**
 * スプライトをまとめたスプライトではなくて、実際の絵を持つスプライトを表す。
 */
class RawSprite: public saccubus::draw::Sprite {
public:
	class Session{
	private:
		Sprite::Handler<RawSprite> const sprite;
		void* _data;
		int _w;
		int _h;
		int _stride;
	public:
		Session(Sprite::Handler<RawSprite> spr);
		virtual ~Session();
	public:
		void* data() const;
		int width() const;
		int height() const;
		int stride() const;
	};
private:
	std::tr1::shared_ptr<Renderer*> _renderer;
	bool _locked;
	int _width;
	int _height;
	int _origWidth;
	int _origHeight;
public:
	virtual int width() const;
	virtual int height() const;
protected:
	int origWidth() const;
	int origHeight() const;
	void width(int val);
	void height(int val);
protected:
	RawSprite(std::tr1::shared_ptr<Renderer*> _renderer);
	RawSprite(std::tr1::shared_ptr<Renderer*> _renderer, int w, int h);
	Renderer* renderer(){ return *(_renderer.get()); };
public:
	virtual ~RawSprite();
protected:
	virtual void lock(void** data, int* w, int* h, int* stride) = 0;
	virtual void unlock() = 0;
	virtual void onFree();
public:
	virtual void draw(std::tr1::shared_ptr<draw::Context> ctx, int x, int y) = 0;
	virtual void resize(int w, int h);
};

}}
