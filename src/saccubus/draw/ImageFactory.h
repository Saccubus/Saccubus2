/*
 * ImageFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef DRAW_IMAGEFACTORY_H_
#define DRAW_IMAGEFACTORY_H_

#include "RawSprite.h"
#include "../classdefs.h"
#include <vector>
#include <tr1/memory>

namespace saccubus {
namespace draw {

class ImageFactory {
public:
	ImageFactory();
	virtual ~ImageFactory();
private:
	const std::tr1::shared_ptr<ImageFactory*> _handler;
protected:
	const std::tr1::shared_ptr<ImageFactory*> handler() { return _handler; };
private:
	struct order
	{
		bool operator() (const Sprite* a, const Sprite* b);
		bool operator() (const Sprite* a, const std::pair<int,int>& b);
		bool operator() (const std::pair<int,int>& a, const Sprite* b);
	};
	// スプライトの大きさは変わる可能性があるが、unused状態であり変更されることはない。
	std::vector<RawSprite*> unusedSprites;
	typedef std::vector<RawSprite*>::iterator SpriteIterator;
public:
	RawSprite::Handler querySprite(int w, int h);
	std::size_t availableSprites();
public: /* Spriteからのコールバック関数 */
	void backSprite(RawSprite* spr);
protected: /* 各実装がこれを実際に実装する */
	virtual RawSprite* createSprite(int w, int h) = 0;
};

}}
#endif /* DRAW_IMAGEFACTORY_H_ */
