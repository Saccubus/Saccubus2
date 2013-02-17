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
#include "RawSprite.h"
#include "../classdefs.h"
#include <vector>
#include <tr1/memory>
#include <cmath>

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
	logging::Logger& log;
public:
	Renderer(logging::Logger& log);
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
	Sprite::Handler<RawSprite> queryRawSprite(int w, int h);
	std::size_t availableRawSprites();
public: /* Spriteからのコールバック関数 */
	void backRawSprite(RawSprite* spr);
public: /* 各実装がこれを実際に実装する */
	virtual std::tr1::shared_ptr<saccubus::draw::Context> createContext(enum Format fmt, void* data, int w, int h, int stride) = 0;
	virtual RawSprite* createRawSprite(enum draw::Renderer::Format fmt, void* data, int w, int h, int stride) = 0;
	virtual RawSprite* createRawSprite(int w, int h) = 0;
};

}}
