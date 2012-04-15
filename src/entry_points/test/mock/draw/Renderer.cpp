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

Renderer::Renderer()
:saccubus::draw::Renderer(640, 480){
	// TODO Auto-generated constructor stub

}

Renderer::~Renderer() {
	// TODO Auto-generated destructor stub
}

saccubus::draw::RawSprite* Renderer::createSprite(int w, int h)
{
	return new Sprite(handler(), w, h);
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
