/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include <algorithm>
#include "Renderer.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

const std::string TAG("draw::Renderer");

Renderer::Renderer(cinamo::Logger& log)
:log(log),_handler(new Renderer*(this))
{
}

Renderer::~Renderer() {
	*(handler().get()) = 0;
	for(SpriteIterator it = unusedSprites.begin(); it != unusedSprites.end(); ++it){
		delete *it;
	}
}

Sprite::Handler<RawSprite> Renderer::queryRawSprite(int w, int h)
{
	SpriteIterator it = std::upper_bound(unusedSprites.begin(), unusedSprites.end(), std::pair<int, int>(w,h), order());
	if(it == unusedSprites.end()){
		Sprite::Handler<RawSprite> handler(createRawSprite(w, h));
		return handler;
	}else{
		Sprite::Handler<RawSprite> handler(*it);
		unusedSprites.erase(it);
		handler->resize(w, h);
		return handler;
	}
}

void Renderer::backRawSprite(RawSprite* spr)
{
	SpriteIterator it = std::lower_bound(unusedSprites.begin(), unusedSprites.end(), spr, order());
	unusedSprites.insert(it, spr);
	while(MaxCachedRawSprites < unusedSprites.size()){
		//TODO: まんなかぐらいの大きさのスプライトを残す
		RawSprite* deleted = 0;
		if((rand() & 1U) == 1U){
			deleted = unusedSprites.back();
			unusedSprites.pop_back();
		}else{
			deleted = unusedSprites.front();
			unusedSprites.erase(unusedSprites.begin());
		}
		if(deleted){
			RawSprite* min = unusedSprites.front();
			RawSprite* max = unusedSprites.back();
			log.d(TAG, "Sprite cache deleted. size: %dx%d / min:%dx%d, max:%dx%d",
					deleted->width(), deleted->height(),
					min->width(), min->height(),
					max->width(), max->height());
			delete deleted;
		}
	}
}

std::size_t Renderer::availableRawSprites()
{
	return unusedSprites.size();
}

bool Renderer::order::operator ()(const Sprite* a, const Sprite* b)
{
	return a->width() <= b->width() && a->height() <= b->height();
}
bool Renderer::order::operator() (const Sprite* a, const std::pair<int,int>& b)
{
	return a->width() <= b.first && a->height() <= b.second;
}
bool Renderer::order::operator() (const std::pair<int,int>& a, const Sprite* b)
{
	return a.first <= b->width() && a.second <= b->height();
}

}}

