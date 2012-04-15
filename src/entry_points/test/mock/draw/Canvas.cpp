/*
 * Canvas.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "Canvas.h"
#include "Sprite.h"

namespace saccubus {
namespace mock {
namespace draw {

Canvas::Canvas() {
	// TODO Auto-generated constructor stub

}

Canvas::~Canvas() {
	// TODO Auto-generated destructor stub
}

void Canvas::draw(int x, int y, Sprite* spr)
{
	this->drawQuery.push_back(std::pair<std::pair<int,int>,Sprite* >(std::pair<int, int>(x, y), spr));
}

Canvas::QueryIterator Canvas::queryBegin()
{
	return this->drawQuery.begin();
}
Canvas::QueryIterator Canvas::queryEnd()
{
	return this->drawQuery.end();
}
std::size_t Canvas::querySize()
{
	return this->drawQuery.size();
}


}}}
