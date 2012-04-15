/*
 * CommentFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef COMMENTFACTORY_H_
#define COMMENTFACTORY_H_

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
	virtual RawSprite::Handler renderComment(const context::Comment* comment) = 0;
};

}}
#endif /* COMMENTFACTORY_H_ */
