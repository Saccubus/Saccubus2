/*
 * Comment.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef COMMENT_H_
#define COMMENT_H_

#include <tr1/memory>
#include "../classdefs.h"
#include "../util/ClassAccessor.h"

namespace nekomata{
namespace system{
class Comment;
}}
namespace saccubus {
namespace context {

class Comment {
	DEF_ATTR_ACCESSOR(public, private, const meta::Comment*, comment);
public:
	Comment(const meta::Comment* comment);
	virtual ~Comment();
public:
public:
	std::tr1::shared_ptr<nekomata::system::Comment> createNekomataComment();
};

}}
#endif /* COMMENT_H_ */
