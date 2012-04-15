/*
 * SpriteFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef SPRITEFACTORY_H_
#define SPRITEFACTORY_H_

#include "RawSprite.h"
#include "../classdefs.h"
#include <vector>
#include <tr1/memory>

namespace saccubus {
namespace draw {

class SpriteFactory {
public:
	SpriteFactory();
	virtual ~SpriteFactory();
private:
	const std::tr1::shared_ptr<SpriteFactory*> _handler;
protected:
	const std::tr1::shared_ptr<SpriteFactory*> handler() { return _handler; };
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
#endif /* SPRITEFACTORY_H_ */
