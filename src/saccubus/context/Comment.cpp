/*
 * Comment.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */
#include "Comment.h"
#include "../meta/Comment.h"

namespace saccubus {
namespace context {

Comment::Comment(const meta::Comment* comment)
{
	this->orig(comment);
}

Comment::~Comment() {
	// TODO Auto-generated destructor stub
}

void Comment::interpret()
{
	for(meta::Comment::MailIterator it= this->orig()->mailBegin(); it != this->orig()->mailEnd(); ++it){
		Comment::interpret(*it, this);
	}
}


}}
