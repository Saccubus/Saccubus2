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

#include "Button.h"
#include "../NekomataSystem.h"
#include "../CommentLayer.h"
#include "../../draw/LayerdSprite.h"
#include "../../draw/CommentFactory.h"
#include "../../draw/ShapeFactory.h"

namespace saccubus {
namespace layer {
namespace item {

Button::Button(
	draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory,
	NekomataSystem* const nekoSystem, CommentLayer* const postLayer,
	bool fromButton, bool isYourPost, const bool isPremium, enum Layer layer,
	const float& vpos, const std::string& message, const std::string& mail,
	const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden
	)
:Comment(commentFactory, shapeFactory, fromButton, isYourPost, isPremium, layer, vpos, message, mail)
,isClicked(0)
,nekoSystem(nekoSystem)
,postLayer(postLayer)
{
	//FIXME: うまい方法ないかなあ
	this->buttonColor(this->color());
	//ボタンの文字色は、どのような色を設定しても白固定で、背景の色だけ変わるっぽい（？）
	this->color(0xffffff);
	this->shadowColor(0x000000);

	this->commes(commes);
	this->commail(commail);
	this->comvisible(comvisible);
	this->limit(limit);
	this->hidden(hidden);
}

Button::~Button() {
}

bool Button::isButton() const
{
	return true;
}

bool Button::onClick(int relX, int relY)
{
	relX -= this->btnRelX;
	relY -= this->btnRelY;
	if(this->limit() <= 0 || !(0 <= relX && relX <= this->buttonSprite->width() && 0 <= relY && relY <= this->buttonSprite->height())){
		return false;
	}
	if(comvisible()){
		std::tr1::shared_ptr<item::Comment> post(
				new Comment(
						commentFactory(), shapeFactory(),
						true, true, true, Comment::Forked,
						nekoSystem->currentTime(), this->commes(), this->commail()
						)
		);
		postLayer->queueComment(post);
	}else if(postLayer){
		std::tr1::shared_ptr<item::Comment> post(
				new Comment(
						commentFactory(), shapeFactory(),
						true, true, true, Comment::Script,
						nekoSystem->currentTime(), this->commes(), this->commail()
						)
		);
		nekoSystem->queueMessage(post->createNekomataMessage());
	}
	isClicked = 3;
	invalidate();
	return true;
}
draw::Sprite::Handler<draw::Sprite> Button::createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx)
{
	if(!leftSprite){
		size_t left = this->message().find("[");
		if(left != std::string::npos){
			std::string leftString(this->message().substr(0, left));
			Comment com(this->commentFactory(), this->shapeFactory(),
					this->fromButton(), this->isYourPost(), this->isPremium(), this->layer(),
					this->vpos(), leftString, this->mail());
			leftSprite = this->commentFactory()->renderCommentText(ctx, &com);
			this->message(this->message().substr(left+1));
		}
	}
	if(!rightSprite){
		size_t right = this->message().find("]");
		if(right != std::string::npos){
			std::string rightString(this->message().substr(right+1));
			Comment com(this->commentFactory(), this->shapeFactory(),
					this->fromButton(), this->isYourPost(), this->isPremium(), this->layer(),
					this->vpos(), rightString, this->mail());
			rightSprite = this->commentFactory()->renderCommentText(ctx, &com);
			this->message(this->message().substr(0, right));
		}
	}
	if(!textSprite){
		this->textSprite = this->commentFactory()->renderCommentText(ctx, this);
	}
	{
		draw::Sprite::Handler<draw::LayerdSprite> layerd = draw::LayerdSprite::newInstance();
		unsigned int color = 0;
		if(this->limit() <= 0){
			color = 0x888888;
		}else if(isClicked){
			color = ~this->buttonColor();
		}else{
			color = this->buttonColor();
		}
		draw::Sprite::Handler<draw::Sprite> btnSpr = this->shapeFactory()->renderButton(ctx, textSprite->width(), textSprite->height(), color);
		layerd->addSprite(0, 0, btnSpr);
		layerd->addSprite((btnSpr->width()-textSprite->width())/2, (btnSpr->height()-textSprite->height())/2, textSprite);
		this->buttonSprite = layerd;
	}
	draw::Sprite::Handler<draw::LayerdSprite> spr = draw::LayerdSprite::newInstance();
	float x = 0.0f;
	if(leftSprite){
		spr->addSprite(0, 0, leftSprite);
		x += this->leftSprite->width();
	}
	btnRelX = x;
	btnRelY = 0;
	spr->addSprite(btnRelX, btnRelY, this->buttonSprite);
	x += this->buttonSprite->width();
	if(rightSprite){
		spr->addSprite(0, 0, rightSprite);
	}
	return spr;
}

void Button::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, int x, int y)
{
	this->Comment::draw(ctx, x, y);
	if(isClicked > 0 && (--isClicked) == 0){
		invalidate();
	}
}

}}}
