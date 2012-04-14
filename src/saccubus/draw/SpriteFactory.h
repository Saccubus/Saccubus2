/*
 * SpriteFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef SPRITEFACTORY_H_
#define SPRITEFACTORY_H_

#include "Sprite.h"
#include "../classdefs.h"
#include <vector>
#include <tr1/memory>

namespace saccubus {
namespace draw {

class SpriteFactory {
public:
	SpriteFactory();
	virtual ~SpriteFactory();
protected:
	virtual Sprite* createSprite(int w, int h) = 0;
private:
	const std::tr1::shared_ptr<SpriteFactory*> handler;
	struct order
	{
		bool operator() (const Sprite* a, const Sprite* b);
		bool operator() (const Sprite* a, const std::pair<int,int>& b);
		bool operator() (const std::pair<int,int>& a, const Sprite* b);
	};
	// スプライトの大きさは変わる可能性があるが、unused状態であり変更されることはない。
	std::vector<Sprite*> unusedSprites;
	typedef std::vector<Sprite*>::iterator SpriteIterator;
public:
	Sprite::Handler querySprite(int w, int h);
	std::size_t availableSprites();
public:
	void backSprite(Sprite* spr);
};

}}
#endif /* SPRITEFACTORY_H_ */
