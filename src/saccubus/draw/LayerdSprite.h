/*
 * LayerdSprite.h
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#ifndef LAYERDSPRITE_H_
#define LAYERDSPRITE_H_

#include <vector>
#include "../classdefs.h"
#include "Sprite.h"

namespace saccubus {
namespace draw {

class LayerdSprite: public saccubus::draw::Sprite {
private:
	std::vector<std::pair<Point, Sprite::Handler<Sprite> > > sprites;
public:
	LayerdSprite();
	virtual ~LayerdSprite();
private:
	void updateSize();
public:
	virtual void draw(Renderer* renderer, int x, int y);
	std::size_t size();
	void addSprite(int x, int y, Sprite::Handler<Sprite> spr);
	virtual void onFree();
};

}}
#endif /* LAYERDSPRITE_H_ */
