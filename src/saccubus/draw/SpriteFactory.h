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
#include <map>
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
		bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b);
	};
	std::multimap<std::pair<int, int>, Sprite*, order> unusedSprites;
	typedef std::multimap<std::pair<int, int>, Sprite*, order>::iterator SpriteIterator;
public:
	Sprite::Handler querySprite(int w, int h);
	std::size_t availableSprites();
public:
	void backSprite(Sprite* spr);
};

}}
#endif /* SPRITEFACTORY_H_ */
