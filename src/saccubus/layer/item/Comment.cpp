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
#include "../../draw/CommentFactory.h"
#include "../../draw/ShapeFactory.h"
#include "../../util/StringUtil.h"

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("item::Comment");

Comment::Comment()
{
	this->commentFactory(0);
	this->shapeFactory(0);
	init();
}
Comment::Comment(const Comment& other)
{
	this->message(other.message());
	this->no(other.no());
	this->from(other.from());
	this->vpos(other.vpos());
	this->to(other.to());
	this->isYourPost(other.isYourPost());
	this->fromButton(other.fromButton());
	this->isPremium(other.isPremium());
	this->full(other.full());
	this->sage(other.sage());
	this->patissier(other.patissier());
	this->device(other.device());
	this->visibility(other.visibility());
	this->size(other.size());
	this->layer(other.layer());
	this->placeY(other.placeY());
	this->color(other.color());
	this->mail(other.mail());
	this->shadowColor(other.shadowColor());
}
Comment& Comment::operator = (const Comment& other)
{
	this->message(other.message());
	this->no(other.no());
	this->from(other.from());
	this->vpos(other.vpos());
	this->to(other.to());
	this->isYourPost(other.isYourPost());
	this->fromButton(other.fromButton());
	this->isPremium(other.isPremium());
	this->full(other.full());
	this->sage(other.sage());
	this->patissier(other.patissier());
	this->device(other.device());
	this->visibility(other.visibility());
	this->size(other.size());
	this->layer(other.layer());
	this->placeY(other.placeY());
	this->color(other.color());
	this->mail(other.mail());
	this->shadowColor(other.shadowColor());
	return *this;
}
Comment::Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory)
{
	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);
	init();
}

Comment::~Comment() {
}

void Comment::init(){
	this->message("");
	this->mail("");
	this->no(-1);
	this->from(NAN);
	this->vpos(NAN);
	this->to(NAN);

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

void Comment::fixTime()
{
	if(this->placeY() == item::Comment::Top || this->placeY() == item::Comment::Bottom){
		this->from(this->vpos());
		this->to(this->from() + this->span() );
	}else{
		this->from(this->vpos()-1.0f);
		this->to(this->from() + this->span() );
	}
}

void Comment::import(const meta::Comment* orig)
{
	this->message(orig->message());
	this->mail(orig->mail());
	this->no(orig->no());
	this->from(orig->vpos()-1.0f);
	this->vpos(orig->vpos());
	this->to(this->from()+4.0f);
	this->isPremium(orig->premium());
	this->layer(orig->fork() ? Comment::Forked : Comment::Normal);
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

void Comment::sizeType(enum Size size)
{
	this->_sizeType = size;
	this->size(size);
}
enum Comment::Size Comment::sizeType() const
{
	return _sizeType;
}

bool Comment::isButton() const
{
	return false;
}
std::string Comment::mail() const
{
	return _mail;
}
void Comment::mail(const std::string& val)
{
	_mail = val;
	_mails.clear();
	util::splitSpace(_mail, this->_mails);
}

size_t Comment::mailSize() const
{
	return _mails.size();
}
Comment::MailIterator Comment::mailBegin() const
{
	return _mails.begin();
}
Comment::MailIterator Comment::mailEnd() const
{
	return _mails.end();
}

}}}
