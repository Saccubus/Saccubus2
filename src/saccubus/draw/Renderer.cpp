/*
 * Renderer.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include <algorithm>
#include "Renderer.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace draw {

Renderer::Renderer(logging::Logger& log, const int w, const int h)
:log(log),_handler(new Renderer*(this))
{
	this->width(w);
	this->height(h);
}

Renderer::~Renderer() {
	*(handler().get()) = 0;
	for(SpriteIterator it = unusedSprites.begin(); it != unusedSprites.end(); ++it){
		delete *it;
	}
}

Sprite::Handler<RawSprite> Renderer::queryRawSprite(int w, int h)
{
	SpriteIterator it = std::lower_bound(unusedSprites.begin(), unusedSprites.end(), std::pair<int, int>(w,h), order());
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
	SpriteIterator it = std::upper_bound(unusedSprites.begin(), unusedSprites.end(), spr, order());
	unusedSprites.insert(it, spr);
	while(MaxCachedRawSprites < unusedSprites.size()){
		//TODO: まんなかぐらいの大きさのスプライトを残す
		RawSprite* deleted = 0;
		if((unusedSprites.size() & 1U) == 1U){
			deleted = unusedSprites.back();
			unusedSprites.pop_back();
		}else{
			deleted = unusedSprites.front();
			unusedSprites.erase(unusedSprites.begin());
		}
		if(deleted){
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
	return a->width() < b->width() && a->height() < b->height();
}
bool Renderer::order::operator() (const Sprite* a, const std::pair<int,int>& b)
{
	return a->width() < b.first && a->height() < b.second;
}
bool Renderer::order::operator() (const std::pair<int,int>& a, const Sprite* b)
{
	return a.first < b->width() && a.second < b->height();
}

}}

