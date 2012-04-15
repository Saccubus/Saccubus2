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
	Point(int x, int y){this->x(x);this->y(y);};
	Point(const Point& other){this->x(other.x());this->y(other.y());};
	~Point(){};
};

class Sprite {
public:
	template<class S>
	class Handler
	{
	public:
		S* sprite;
	public:
		Handler():sprite(0){};
		template<class T>
		explicit Handler(T* const sprite)
		:sprite(dynamic_cast<S*>(sprite))
		{
			if(this->sprite){
				if(this->sprite->refcount != 0){
					throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite::Handler created, but refcount = %d, not zero.", this->sprite->refcount);
				}
				this->sprite->incref();
			}
		}
		Handler(const Handler<S>& other)
		:sprite(other.sprite)
		{
			if(this->sprite){
				this->sprite->incref();
			}
		}
		template<class T>
		Handler(const Handler<T>& other)
		:sprite(dynamic_cast<S*>(other.sprite))
		{
			if(this->sprite){
				this->sprite->incref();
			}
		}
		Handler<S>& operator=(const Handler<S>& other)
		{
			if(other.sprite){
				other.sprite->incref();
			}
			if(this->sprite){
				this->sprite->decref();
			}
			this->sprite = other.sprite;
			return *this;
		}
		template<class T>
		Handler<S>& operator=(const Handler<T>& other)
		{
			S* spr = dynamic_cast<S*>(other.sprite);
			if(spr){
				spr->incref();
			}
			if(this->sprite){
				this->sprite->decref();
			}
			this->sprite = spr;
			return *this;
		}
		virtual ~Handler()
		{
			if(this->sprite){
				this->sprite->decref();
			}
		}
		S* operator->() const
		{
			return this->sprite;
		}
		S* get() const
		{
			return this->sprite;
		}
		operator bool() const
		{
			return this->sprite != 0;
		}
	};
	DEF_ATTR_ACCESSOR(public, protected, int, width);
	DEF_ATTR_ACCESSOR(public, protected, int, height);
private:
	int refcount;
	void incref();
	void decref();
protected:
	Sprite();
	Sprite(int w, int h);
public:
	virtual ~Sprite();
protected:
	virtual void onFree() = 0;
public:
	virtual void draw(Renderer* renderer, int x, int y) = 0;
	virtual void shrink(int w, int h) = 0;
};


}}


#endif /* SPRITE_H_ */
