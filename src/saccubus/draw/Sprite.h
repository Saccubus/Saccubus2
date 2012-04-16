/*
 * Sprite.h
 *
 *  Created on: 2012/03/27
 *      Author: psi
 */

#ifndef DRAW_SPRITE_H_
#define DRAW_SPRITE_H_

#include <tr1/memory>
#include "../logging/Exception.h"
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
	private:
		S* sprite;
	public:
		static Handler<S> __internal__fromRawPointerWithoutCheck(S* const sprite)
		{
			Handler<S> spr;
			spr.sprite = sprite;
			if(spr.sprite){
				spr.sprite->incref();
			}
			return spr;
		}
		Handler():sprite(0){};
		explicit Handler(S* const sprite)
		:sprite(sprite)
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
		template <class T>
		Handler(const Handler<T>& other)
		:sprite(other.get())
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
		template <class T>
		Handler<S>& operator=(const Handler<T>& other)
		{
			if(other.get()){
				other.get()->incref();
			}
			if(this->sprite){
				this->sprite->decref();
			}
			this->sprite = other.get();
			return *this;
		}
		template<class T>
		Handler<T> cast() const
		{
			T* spr = dynamic_cast<T*>(this->sprite);
			if(!spr){
				throw logging::Exception(__FILE__, __LINE__, "[BUG] Sprite::Handler / failed to cast %s to %s", typeid(this->sprite).name(), typeid(spr).name());
			}
			return Handler<T>::__internal__fromRawPointerWithoutCheck(spr);
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
public:
	virtual int width() const = 0;
	virtual int height() const = 0;
private:
	int refcount;
	void incref();
	void decref();
protected:
	Sprite();
public:
	virtual ~Sprite();
protected:
	virtual void onFree() = 0;
public:
	virtual void draw(Renderer* renderer, int x, int y) = 0;
	virtual void resize(int w, int h) = 0;
};


}}


#endif /* DRAW_SPRITE_H_ */
