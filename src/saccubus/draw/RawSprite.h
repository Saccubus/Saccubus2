/*
 * RawSprite.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef RAWSPRITE_H_
#define RAWSPRITE_H_

#include "Sprite.h"

namespace saccubus {
namespace draw {
/**
 * スプライトをまとめたスプライトではなくて、実際の絵を持つスプライトを表す。
 */
class RawSprite: public saccubus::draw::Sprite {
public:
	class Handler
	{
	private:
		RawSprite* sprite;
	public:
		explicit Handler(RawSprite* const sprite);
	public:
		Handler();
		Handler(const Handler& other);
		Handler& operator=(const Handler& other);
		virtual ~Handler();
		RawSprite* operator->() const;
		RawSprite* operator*() const;
		operator bool() const;
	};
private:
	int refcount;
	std::tr1::shared_ptr<Renderer*> _renderer;
	void incref();
	void decref();
protected:
	RawSprite(std::tr1::shared_ptr<Renderer*> _renderer);
	RawSprite(std::tr1::shared_ptr<Renderer*> _renderer, int w, int h);
	Renderer* renderer(){ return *(_renderer.get()); };
public:
	virtual ~RawSprite();
public:
	virtual void draw(Renderer* renderer, int x, int y) = 0;
	virtual void shrink(int w, int h);
};

}}
#endif /* RAWSPRITE_H_ */
