/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <vector>
#include <cmath>
#include <cinamo/Logger.h>
#include "RawSprite.h"
#include "../classdefs.h"

namespace saccubus {
namespace draw {

constexpr const std::size_t MaxCachedRawSprites = 100;
#ifdef M_PI
constexpr const float PI=M_PI;
#else
constexpr const float PI=3.1415926535897932384626433832795028841971693993751058209;
#endif

class Renderer {
public:
	enum Format {
		ARGB32,
		RGB32
	};
protected:
	cinamo::Logger& log;
public:
	Renderer(cinamo::Logger& log);
	virtual ~Renderer();
/**************************************************************************************************
 * スプライト管理機構
 **************************************************************************************************/
private:
	const std::shared_ptr<Renderer*> _handler;
protected:
	const std::shared_ptr<Renderer*> handler() { return _handler; };
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
	Sprite::Handler<RawSprite> queryRawSprite(int w, int h);
	std::size_t availableRawSprites();
public: /* Spriteからのコールバック関数 */
	void backRawSprite(RawSprite* spr);
public: /* 各実装がこれを実際に実装する */
	virtual std::shared_ptr<saccubus::draw::Context> createContext(enum Format fmt, void* data, int w, int h, int stride) = 0;
	virtual RawSprite* createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride) = 0;
	virtual RawSprite* createRawSprite(int w, int h) = 0;
};

}}
