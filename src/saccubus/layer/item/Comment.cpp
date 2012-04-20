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

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("item::Comment");

Comment::Comment()
{
	this->orig(0);
	this->commentFactory(0);
	this->shapeFactory(0);
	this->setDefault();
}
Comment::Comment(const meta::Comment* comment, draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory)
{
	this->orig(comment);
	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);
	this->setDefault();
}

Comment::~Comment() {
}

void Comment::setDefault()
{
	this->message(orig() ? orig()->message() : "");
	this->from(orig() ? orig()->vpos()-1.0f : NAN);
	this->to(this->from()+4.0f);
	this->isButton(false);
	this->isYourPost(false);
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
	this->layer((orig() && orig()->fork()) ? Comment::Forked : Comment::Normal);
}

std::tr1::shared_ptr<nekomata::system::Comment> Comment::createNekomataComment()
{
	return std::tr1::shared_ptr<nekomata::system::Comment>(new nekomata::system::Comment(
			this->message(),
			this->orig()->vpos(),
			this->isYourPost(),
			this->orig()->mail(),
			this->fromButton(),
			this->orig()->premium(),
			this->color(),
			this->size(),
			this->orig()->no()
			));
}

draw::Sprite::Handler<draw::Sprite> Comment::createSprite()
{
	if(!this->isButton()){
		return commentFactory()->renderComment(this, 1);
	}
}

bool Comment::onClick()
{
	return true;
}


}}}
