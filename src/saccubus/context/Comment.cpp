/*
 * Comment.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */
#include "Comment.h"
#include <cmath>
#include "../meta/Comment.h"

namespace saccubus {
namespace context {

static const std::string TAG("context/Comment");

Comment::Comment()
{
	this->orig(0);
	this->setDefault();
}
Comment::Comment(logging::Logger& log, const meta::Comment* comment)
{
	this->orig(comment);
	this->setDefault();
	this->interpret(log);
}

Comment::~Comment() {
	// TODO Auto-generated destructor stub
}

void Comment::setDefault()
{
	this->from(orig() ? orig()->vpos()-1.0f : NAN);
	this->to(orig() ? orig()->vpos()+2.0f : NAN);
	this->isButton(false);
	this->fromButton(false);
	this->full(false);
	this->sage(true);
	this->patissier(false);
	this->device(Comment::Unspecified);
	this->visibility(true);
	this->size(Comment::Medium);
	this->placeX(Comment::Center);
	this->placeY(Comment::Middle);
	this->color(0xFFFFFF);
	this->shadowColor(0x000000);
}

void Comment::interpret(logging::Logger& log)
{
	for(meta::Comment::MailIterator it= this->orig()->mailBegin(); it != this->orig()->mailEnd(); ++it){
		if(!Comment::interpret(*it, this))
		{
			log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}
}


}}
