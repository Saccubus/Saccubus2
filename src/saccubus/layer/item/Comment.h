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
#include <nekomata/system/System.h>
#include <string>
#include <tr1/memory>
#include <tr1/functional>
#include <vector>
#include "Item.h"
#include "../../classdefs.h"
#include "../../util/ClassAccessor.h"
#include "../../draw/Sprite.h"

namespace nekomata{
namespace system{
class Message;
}}
namespace saccubus {
namespace layer {
namespace item {

class Comment : public Item {
	DEF_ATTR_ACCESSOR(protected, private, draw::CommentFactory*, commentFactory);
	DEF_ATTR_ACCESSOR(protected, private, draw::ShapeFactory*, shapeFactory);
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
	DEF_ATTR_ACCESSOR(public , private, std::string, originalMessage);
	DEF_ATTR_ACCESSOR(public , protected, std::string, message);
	DEF_ATTR_ACCESSOR(public , private  , std::string, mail);
	DEF_ATTR_ACCESSOR(public , private  , unsigned int, no);
	DEF_ATTR_ACCESSOR(public , private  , float, from);
	DEF_ATTR_ACCESSOR(public , private  , float, vpos);
	DEF_ATTR_ACCESSOR(private, private  , float, span);
	DEF_ATTR_ACCESSOR(public , private  , float, to);
	DEF_ATTR_ACCESSOR(public , private  , bool, isYourPost);
	DEF_ATTR_ACCESSOR(public , private  , bool, fromButton);
	DEF_ATTR_ACCESSOR(public , private  , bool, isPremium);
	DEF_ATTR_ACCESSOR(public , private  , bool, full);
	DEF_ATTR_ACCESSOR(public , private  , bool, sage);
	DEF_ATTR_ACCESSOR(public , private  , bool, patissier);
	DEF_ATTR_ACCESSOR(public , private  , enum Device, device);
	DEF_ATTR_ACCESSOR(public , private  , bool, visibility);
	DEF_ATTR_ACCESSOR(public , private  , enum Size, sizeType);
	DEF_ATTR_ACCESSOR(public , private  , enum Layer, layer);
	DEF_ATTR_ACCESSOR(public , private  , enum PlaceY, placeY);
	DEF_ATTR_ACCESSOR(public , protected, unsigned int, color);
	DEF_ATTR_ACCESSOR(public , protected, unsigned int, shadowColor);
private:
	Comment();
	Comment& operator = (const Comment& other);
public:
	Comment(const Comment& other);
	Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, const meta::ReplaceTable* replaceTable, const meta::Comment* meta);
	Comment(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory,
			bool fromButton, bool isYourPost, const bool isPremium, enum Layer layer,
			const float& vpos, const std::string& message, const std::string& mail
			);
	virtual ~Comment();
public:
	std::tr1::shared_ptr<nekomata::system::Message> createNekomataMessage();
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
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx);
/* 補助的なデータ構造他 */
public:
	struct StartTimeCompare{
		bool operator() (const Comment& a, const Comment& b);
		bool operator() (const Comment& a, const float& b);
		bool operator() (const float& a, const Comment& b);
		bool operator() (const Comment* a, const Comment* b);
		bool operator() (const float& a, const Comment* b);
		bool operator() (const Comment* a, const float& b);
		bool operator() (const std::tr1::shared_ptr<Comment>& a, const std::tr1::shared_ptr<Comment>& b);
		bool operator() (const float& a, const std::tr1::shared_ptr<Comment>& b);
		bool operator() (const std::tr1::shared_ptr<Comment>& a, const float& b);
	};
private:
	struct MailOperation;
	struct NekomataReplaceOperation;
};

}}}
