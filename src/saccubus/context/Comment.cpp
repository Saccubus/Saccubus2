/*
 * Comment.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "Comment.h"

namespace saccubus {
namespace context {

Comment::Comment(const meta::Comment* comment)
{
	this->comment(comment);
}

Comment::~Comment() {
	// TODO Auto-generated destructor stub
}

}}
