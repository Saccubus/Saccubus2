/*
 * Renderer.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#include "Renderer.h"
#include "Sprite.h"

namespace saccubus {
namespace mock {
namespace draw {

Renderer::Renderer(logging::Logger& log)
:saccubus::draw::Renderer(log, 640, 480){
}

Renderer::~Renderer() {
}

saccubus::draw::RawSprite* Renderer::createRawSprite(int w, int h)
{
	return new Sprite(log, handler(), w, h);
}

void Renderer::draw(int x, int y, Sprite* spr)
{
	this->drawQuery.push_back(std::pair<std::pair<int,int>,Sprite* >(std::pair<int, int>(x, y), spr));
}

Renderer::QueryIterator Renderer::queryBegin()
{
	return this->drawQuery.begin();
}
Renderer::QueryIterator Renderer::queryEnd()
{
	return this->drawQuery.end();
}
std::size_t Renderer::querySize()
{
	return this->drawQuery.size();
}
}}}
