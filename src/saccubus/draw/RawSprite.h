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
	std::tr1::shared_ptr<SpriteFactory*> _factory;
	void incref();
	void decref();
	SpriteFactory* factory(){ return *(_factory.get()); };
protected:
	RawSprite(std::tr1::shared_ptr<SpriteFactory*> _factory);
	RawSprite(std::tr1::shared_ptr<SpriteFactory*> _factory, int w, int h);
public:
	virtual ~RawSprite();
public:
	virtual void draw(Canvas* canvas, int x, int y) = 0;
	virtual void shrink(int w, int h);
};

}}
#endif /* RAWSPRITE_H_ */
