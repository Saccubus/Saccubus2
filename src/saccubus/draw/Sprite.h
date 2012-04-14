/*
 * Sprite.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <tr1/memory>
#include "../classdefs.h"
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace draw {

class Point{
	DEF_ATTR_ACCESSOR(public, public, int, x);
	DEF_ATTR_ACCESSOR(public, public, int, y);
public:
	Point(int x, int y);
	Point(const Point& other){x(other.x());y(other.y());};
	~Point(){};
};

class Sprite {
	DEF_ATTR_ACCESSOR(public, protected, int, width);
	DEF_ATTR_ACCESSOR(public, protected, int, height);
private:
	int refcount;
public:
	class Handler
	{
	private:
		void incref();
		void decref();
	private:
		Sprite* sprite;
		std::tr1::shared_ptr<SpriteFactory*> factory;
	public:
		explicit Handler(Sprite* const sprite, std::tr1::shared_ptr<SpriteFactory*> factory);
	public:
		Handler();
		Handler(const Handler& other);
		Handler& operator=(const Handler& other);
		virtual ~Handler();
		Sprite* operator->() const;
		Sprite* operator*() const;
		operator bool() const;
	};
protected:
	Sprite();
public:
	Sprite(int w, int h);
	virtual ~Sprite();
	virtual void draw(Canvas* canvas, int x, int y) = 0;
	virtual void shrink(int w, int h);
};

}}

#endif /* SPRITE_H_ */
