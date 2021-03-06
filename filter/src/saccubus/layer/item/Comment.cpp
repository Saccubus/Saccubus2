/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "Comment.h"
#include <cmath>
#include <cinamo/String.h>
#include <nicomo/model/Comment.h>
#include <nicomo/model/ReplaceTable.h>
#include <nekomata/system/System.h>
#include <nekomata/parser/Parser.h>
#include "../../NicoConstant.h"
#include "../../draw/CommentFactory.h"
#include "../../draw/ShapeFactory.h"
#include "../../nicos/NicosTrans.h"

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("item::Comment");

Comment::Comment(
	draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory,
	bool fromButton, bool isYourPost, const bool isPremium, enum Layer layer,
	const float& vpos, std::string const& message, std::string const& mail
){
	init();

	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);

	this->fromButton(fromButton);
	this->isYourPost(isYourPost);
	this->isPremium(isPremium);
	this->layer(layer);

	this->vpos(vpos);
	this->originalMessage(message);
	this->message(message);
	this->mail(mail);

	parse();
}
Comment::Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, const nicomo::model::ReplaceTable* replaceTable, const nicomo::model::Comment* meta)
{
	init();

	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);

	this->originalMessage(meta->message());
	this->message(meta->message());
	this->mail(meta->mail());
	this->no(meta->no());
	this->vpos(meta->vpos());
	this->isPremium(meta->premium());
	this->layer(meta->fork() ? Comment::Forked : Comment::Normal);

	if(replaceTable){
		this->message(replaceTable->replace(this->message()));
	}

	parse();
}
Comment::Comment(const Comment& other)
{
	init();
	this->commentFactory(other.commentFactory());
	this->shapeFactory(other.shapeFactory());

	this->originalMessage(other.originalMessage());
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

void Comment::init(){
	this->commentFactory(0);
	this->shapeFactory(0);

	this->originalMessage("");
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
	this->sage(false);
	this->patissier(false);
	this->device(Comment::Unspecified);
	this->visibility(true);
	this->sizeType(Comment::Medium);
	this->placeY(Comment::Middle);
	this->color(0xFFFFFF);
	this->shadowColor(0x000000);
	this->layer(Comment::Normal);
}

void Comment::parse()
{
	std::vector<std::string> const lst ( cinamo::splitSpace(this->mail()) );

	if(cinamo::startsWith(this->originalMessage(), std::string(u8"/"))){ /* スクリプト */
		this->node(nekomata::parser::Parser::fromString(this->originalMessage().substr(1), this->message(), static_cast<int>(this->vpos()*100))->parseProgram());
	} else if(cinamo::startsWith(this->originalMessage(), std::string(u8"＠"))){
		this->node(nekomata::parser::Parser::fromString(nicos::toNiwango(*this), "NicoS", static_cast<int>(this->vpos()*100))->parseProgram());
	}else{
		this->node(nullptr);
	}

	for(std::string const& str : lst){
		if(!this->applyMail(str)){
			//log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}

	const bool spanIsNan = !(this->span() == this->span());
	if(this->placeY() == item::Comment::Top || this->placeY() == item::Comment::Bottom){
		this->from(this->vpos());
		this->to(this->from() + (spanIsNan ? nico::FixedCommentTime : this->span()) );
	}else{
		this->from(this->vpos()-nico::CommentAheadSec);
		this->to(this->from() + (spanIsNan ? nico::FlowingCommentTime : this->span()) );
	}
}


std::shared_ptr<nekomata::system::Message> Comment::createNekomataMessage()
{
	return std::shared_ptr<nekomata::system::Comment>(new nekomata::system::Comment(
			this->originalMessage(),
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

draw::Sprite::Handler<draw::Sprite> Comment::createSprite(std::shared_ptr<saccubus::draw::Context> ctx)
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
