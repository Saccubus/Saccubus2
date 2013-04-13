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
#pragma once
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <nekomata/system/System.h>
#include <cinamo/ClassUtil.h>
#include <nicomo/Model.h>
#include "Item.h"
#include "../../classdefs.h"
#include "../../draw/Sprite.h"

namespace nekomata{
namespace system{
class Message;
}}

namespace saccubus {
namespace layer {
namespace item {

class Comment : public Item {
	DEFINE_MEMBER(protected, private, draw::CommentFactory*, commentFactory);
	DEFINE_MEMBER(protected, private, draw::ShapeFactory*, shapeFactory);
public:
	enum Layer {
		Normal,
		Forked,
		Script
	};
	enum Device {
		Unspecified,
		iPhone,
		docomo,
		softbank
	};
	enum Size{
		Unknwon=0,
		Big=39,
		Small=15,
		Medium=24
	};
	enum PlaceY{
		Top,
		Middle,
		Bottom,
	};
	DEFINE_MEMBER(public , private, std::string, originalMessage);
	DEFINE_MEMBER(public , protected, std::string, message);
	DEFINE_MEMBER(public , private  , std::string, mail);
	DEFINE_MEMBER(public , private  , unsigned int, no);
	DEFINE_MEMBER(public , private  , float, from);
	DEFINE_MEMBER(public , private  , float, vpos);
	DEFINE_MEMBER(private, private  , float, span);
	DEFINE_MEMBER(public , private  , float, to);
	DEFINE_MEMBER(public , private  , bool, isYourPost);
	DEFINE_MEMBER(public , private  , bool, fromButton);
	DEFINE_MEMBER(public , private  , bool, isPremium);
	DEFINE_MEMBER(public , private  , bool, full);
	DEFINE_MEMBER(public , private  , bool, sage);
	DEFINE_MEMBER(public , private  , bool, patissier);
	DEFINE_MEMBER(public , private  , enum Device, device);
	DEFINE_MEMBER(public , private  , bool, visibility);
	DEFINE_MEMBER(public , private  , enum Size, sizeType);
	DEFINE_MEMBER(public , private  , enum Layer, layer);
	DEFINE_MEMBER(public , private  , enum PlaceY, placeY);
	DEFINE_MEMBER(public , protected, unsigned int, color);
	DEFINE_MEMBER(public , protected, unsigned int, shadowColor);
private:
	Comment();
	Comment& operator = (const Comment& other);
public:
	Comment(const Comment& other);
	Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, const nicomo::model::ReplaceTable* replaceTable, const nicomo::model::Comment* meta);
	Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory,
			bool fromButton, bool isYourPost, const bool isPremium, enum Layer layer,
			const float& vpos, const std::string& message, const std::string& mail
			);
	virtual ~Comment() noexcept = default;
public:
	std::shared_ptr<nekomata::system::Message> createNekomataMessage();
	float size() const;
private:
	void init();
	void parse();
	bool applyMail(const std::string& ml);
public:
	void onDeploy(nekomata::system::System* system);
public:
	virtual bool isButton() const;
	/**
	 * Item Methods
	 */
protected:
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::shared_ptr<saccubus::draw::Context> ctx);
/* 補助的なデータ構造他 */
public:
	struct StartTimeCompare{
		bool operator() (const Comment& a, const Comment& b);
		bool operator() (const Comment& a, const float& b);
		bool operator() (const float& a, const Comment& b);
		bool operator() (const Comment* a, const Comment* b);
		bool operator() (const float& a, const Comment* b);
		bool operator() (const Comment* a, const float& b);
		bool operator() (const std::shared_ptr<Comment>& a, const std::shared_ptr<Comment>& b);
		bool operator() (const float& a, const std::shared_ptr<Comment>& b);
		bool operator() (const std::shared_ptr<Comment>& a, const float& b);
	};
private:
	struct MailOperation;
	struct NekomataReplaceOperation;
};

}}}
