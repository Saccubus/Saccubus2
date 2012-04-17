/*
 * CommentFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef DRAW_COMMENTFACTORY_H_
#define DRAW_COMMENTFACTORY_H_

#include "RawSprite.h"
#include "../util/ClassAccessor.h"
namespace saccubus {
namespace draw {

class CommentFactory {
private:
	DEF_ATTR_ACCESSOR(protected, private, Renderer*, renderer);
public:
	CommentFactory(Renderer* renderer);
	virtual ~CommentFactory();
public:
	virtual Sprite::Handler<Sprite> renderComment(const context::Comment* comment, float factor) = 0;
};

}}
#endif /* DRAW_COMMENTFACTORY_H_ */
