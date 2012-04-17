/*
 * RawSprite.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef DRAW_RAWSPRITE_H_
#define DRAW_RAWSPRITE_H_

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
	RawSprite(logging::Logger& log, std::tr1::shared_ptr<Renderer*> _renderer);
	RawSprite(logging::Logger& log, std::tr1::shared_ptr<Renderer*> _renderer, int w, int h);
	Renderer* renderer(){ return *(_renderer.get()); };
public:
	virtual ~RawSprite();
protected:
	virtual void lock(void** data, int* w, int* h, int* stride) = 0;
	virtual void unlock() = 0;
	virtual void onFree();
public:
	virtual void draw(Renderer* renderer, int x, int y) = 0;
	virtual void resize(int w, int h);
};

}}
#endif /* DRAW_RAWSPRITE_H_ */
