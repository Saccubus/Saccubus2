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

#ifndef Saccubus_MESSAGEORGANIZER_H__CPP_
#define Saccubus_MESSAGEORGANIZER_H__CPP_

#include "../classdefs.h"
#include "../util/ClassAccessor.h"
#include "item/Comment.h"
#include "NekomataSystem.h"

namespace saccubus {
namespace layer {

class MessageOrganizer {
	DEF_ATTR_ACCESSOR(private, private, draw::CommentFactory*, commentFactory);
	DEF_ATTR_ACCESSOR(private, private, draw::ShapeFactory*, shapeFactory);
	DEF_ATTR_ACCESSOR(private, private, const meta::ReplaceTable*, replaceTable);
	DEF_ATTR_ACCESSOR(private, private, nekomata::Nekomata*, neko);
	DEF_ATTR_ACCESSOR(private, private, nekomata::system::System*, nekoSystem);
//------
	DEF_ATTR_ACCESSOR(private, private, layer::CommentLayer*, mainCommentLayer);
	DEF_ATTR_ACCESSOR(private, private, layer::CommentLayer*, forkedCommentLayer);
private:
	logging::Logger& log;
public:
	MessageOrganizer(logging::Logger& log, draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, const meta::ReplaceTable* replaceTable, nekomata::Nekomata* neko, layer::NekomataSystem* nekomataSystem);
	virtual ~MessageOrganizer();
public:
	item::Comment* organize(const meta::Comment* comment);
	void rewrite(item::Comment* comment);
};

}}
#endif /* INCLUDE_GUARD */
