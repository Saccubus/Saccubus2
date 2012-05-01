/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Comment.h"
#include <cmath>
#include <nekomata/system/System.h>
#include "../../meta/Comment.h"
#include "../../meta/ReplaceTable.h"
#include "../../draw/CommentFactory.h"
#include "../../draw/ShapeFactory.h"
#include "../../util/StringUtil.h"

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("item::Comment");

Comment::Comment(
	draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory,
	bool fromButton, bool isYourPost, const bool isPremium, enum Layer layer,
	const float& vpos, const std::string& message, const std::string& mail
){
	init();

	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);

	this->fromButton(fromButton);
	this->isYourPost(isYourPost);
	this->isPremium(isPremium);
	this->layer(layer);

	this->vpos(vpos);
	this->message(message);
	this->mail(mail);

	update();
}
Comment::Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, const meta::ReplaceTable* replaceTable, const meta::Comment* meta)
{
	init();

	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);

	this->message(meta->message());
	this->mail(meta->mail());
	this->no(meta->no());
	this->vpos(meta->vpos());
	this->isPremium(meta->premium());
	this->layer(meta->fork() ? Comment::Forked : Comment::Normal);

	if(replaceTable){
		this->message(replaceTable->replace(this->message()));
	}

	update();
}
Comment::Comment(const Comment& other)
{
	init();
	this->commentFactory(other.commentFactory());
	this->shapeFactory(other.shapeFactory());

	this->message(other.message());
	this->mail(other.mail());
	this->no(other.no());
	this->from(other.from());
	this->vpos(other.vpos());
	this->to(other.to());
	this->span(other.span());
	this->isYourPost(other.isYourPost());
	this->fromButton(other.fromButton());
	this->isPremium(other.isPremium());
	this->full(other.full());
	this->sage(other.sage());
	this->patissier(other.patissier());
	this->device(other.device());
	this->visibility(other.visibility());
	this->sizeType(other.sizeType());
	this->layer(other.layer());
	this->placeY(other.placeY());
	this->color(other.color());
	this->shadowColor(other.shadowColor());
}

Comment::~Comment() {
}

void Comment::init(){
	this->commentFactory(0);
	this->shapeFactory(0);

	this->message("");
	this->mail("");
	this->no(-1);
	this->from(NAN);
	this->vpos(NAN);
	this->to(NAN);
	this->span(NAN);

	this->isYourPost(false);
	this->fromButton(false);
	this->isPremium(false);
	this->full(false);
	this->sage(true);
	this->patissier(false);
	this->device(Comment::Unspecified);
	this->visibility(true);
	this->sizeType(Comment::Medium);
	this->placeY(Comment::Middle);
	this->color(0xFFFFFF);
	this->shadowColor(0x000000);
	this->layer(Comment::Normal);
}

void Comment::update()
{
	std::vector<std::string> lst;
	util::splitSpace(this->mail(), lst);
	for(std::vector<std::string>::const_iterator it= lst.begin(); it != lst.end(); ++it){
		if(!this->applyMail(*it)){
			//log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}

	bool spanIsNan = !(this->span() == this->span());
	if(this->placeY() == item::Comment::Top || this->placeY() == item::Comment::Bottom){
		this->from(this->vpos());
		this->to(this->from() + (spanIsNan ? 3 : this->span()) );
	}else{
		this->from(this->vpos()-1.0f);
		this->to(this->from() + (spanIsNan ? 4 : this->span()) );
	}
}


std::tr1::shared_ptr<nekomata::system::Message> Comment::createNekomataMessage()
{
	return std::tr1::shared_ptr<nekomata::system::Comment>(new nekomata::system::Comment(
			this->message(),
			this->vpos(),
			this->isYourPost(),
			this->mail(),
			this->fromButton(),
			this->isPremium(),
			this->color(),
			this->size(),
			this->no()
			));
}

draw::Sprite::Handler<draw::Sprite> Comment::createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx)
{
	return commentFactory()->renderCommentText(ctx, this);
}

float Comment::size() const{
	return this->sizeType();
}

bool Comment::isButton() const
{
	return false;
}

}}}
