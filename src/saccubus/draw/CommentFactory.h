/*
 * CommentFactory.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef COMMENTFACTORY_H_
#define COMMENTFACTORY_H_

#include "Sprite.h"
#include "../util/ClassAccessor.h"
namespace saccubus {
namespace draw {

class CommentFactory {
private:
	DEF_ATTR_ACCESSOR(protected, private, SpriteFactory*, sprFactory);
public:
	CommentFactory(SpriteFactory* sprFactory);
	virtual ~CommentFactory();
public:
	virtual Sprite::Handler renderComment(const context::Comment* comment) = 0;
};

}}
#endif /* COMMENTFACTORY_H_ */
