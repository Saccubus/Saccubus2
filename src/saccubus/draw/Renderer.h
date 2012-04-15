/*
 * Renderer.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef DRAW_RENDERER_H_
#define DRAW_RENDERER_H_
#include "RawSprite.h"
#include "../classdefs.h"
#include <vector>
#include <tr1/memory>

namespace saccubus {
namespace draw {

class Renderer {
	DEF_ATTR_ACCESSOR(public, protected, int, width)
	DEF_ATTR_ACCESSOR(public, protected, int, height)
public:
	Renderer(const int w, const int h);
	virtual ~Renderer();
/**************************************************************************************************
 * スプライト管理機構
 **************************************************************************************************/
private:
	const std::tr1::shared_ptr<Renderer*> _handler;
protected:
	const std::tr1::shared_ptr<Renderer*> handler() { return _handler; };
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
#endif /* DRAW_RENDERER_H_ */
