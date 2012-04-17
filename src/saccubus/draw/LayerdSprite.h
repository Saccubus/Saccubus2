/*
 * LayerdSprite.h
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#ifndef DRAW_LAYERDSPRITE_H_
#define DRAW_LAYERDSPRITE_H_

#include <vector>
#include "../classdefs.h"
#include "Sprite.h"

namespace saccubus {
namespace draw {

class LayerdSprite: public saccubus::draw::Sprite {
private:
	std::vector<std::pair<Point, Sprite::Handler<Sprite> > > sprites;
private:
	LayerdSprite(logging::Logger& log);
public:
	static Sprite::Handler<LayerdSprite> newInstance(logging::Logger& log);
	virtual ~LayerdSprite();
public:
	virtual void draw(Renderer* renderer, int x, int y);
	std::size_t size();
	void addSprite(int x, int y, Sprite::Handler<Sprite> spr);
	virtual void onFree();
	virtual void resize(int w, int h);
	virtual int width() const;
	virtual int height() const;
};

}}
#endif /* DRAW_LAYERDSPRITE_H_ */
