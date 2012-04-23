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

#ifndef Saccubus_BUTTON_H__CPP_
#define Saccubus_BUTTON_H__CPP_

#include "Comment.h"

namespace saccubus {
namespace layer {
namespace item {

class Button: public saccubus::layer::item::Comment {
	DEF_ATTR_ACCESSOR(public, public, std::string, commes);
	DEF_ATTR_ACCESSOR(public, public, bool, comvisible);
	DEF_ATTR_ACCESSOR(public, public, std::string, commail);
	DEF_ATTR_ACCESSOR(public, public, int, limit);
	DEF_ATTR_ACCESSOR(public, public, bool, hidden);
private:
	MessageOrganizer* const organizer;
	NekomataSystem* const nekoSystem;
	CommentLayer* const postLayer;
public:
	Button(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, MessageOrganizer* const organizer, NekomataSystem* const nekoSystem, CommentLayer* const postLayer);
	virtual ~Button();
public:
	virtual bool isButton() const;
public:
	virtual bool onClick();
protected:
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx);
};

}}}
#endif /* INCLUDE_GUARD */
