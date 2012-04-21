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

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("item::Comment");

Comment::Comment()
{
	this->commentFactory(0);
	this->shapeFactory(0);
}
Comment::Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory)
{
	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);
}

Comment::~Comment() {
}

void Comment::setDefault(const meta::Comment* orig)
{
	this->message(orig->message());
	this->mail(orig->mail());
	this->no(orig->no());
	this->from(orig->vpos()-1.0f);
	this->vpos(orig->vpos());
	this->to(this->from()+4.0f);
	this->isButton(false);
	this->isYourPost(false);
	this->fromButton(false);
	this->isPremium(orig->premium());
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
	this->layer((orig->fork()) ? Comment::Forked : Comment::Normal);
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
	if(this->isButton()){
		draw::Sprite::Handler<draw::Sprite> textSpr = this->commentFactory()->renderComment(ctx, this);
		draw::Sprite::Handler<draw::Sprite> btnSpr = this->shapeFactory()->renderButton(ctx, textSpr->width(), textSpr->height(), this->color());
	}else{
		return commentFactory()->renderComment(ctx, this);
	}
}

bool Comment::onClick()
{
	return true;
}


}}}
