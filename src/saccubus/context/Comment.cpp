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
	//デフォルト値の設定
	this->from(orig()->vpos()-1.0f);
	this->to(orig()->vpos()+2.0f);
	this->isButton(false);
	this->fromButton(false);
	this->full(false);
	this->sage(true);
	this->patissier(false);
	this->device(Comment::Unspecified);
	this->vibisle(true);
	this->size(Comment::Medium);
	this->placeX(Comment::Center);
	this->placeY(Comment::Middle);
	this->color(0xFFFFFF);
	this->shadowColor(0x000000);
	//
	this->interpret();
}

Comment::~Comment() {
	// TODO Auto-generated destructor stub
}

void Comment::interpret()
{
	for(meta::Comment::MailIterator it= this->orig()->mailBegin(); it != this->orig()->mailEnd(); ++it){
		if(!Comment::interpret(*it, this))
		{
			//FIXME: 警告表示
		}
	}
}


}}
