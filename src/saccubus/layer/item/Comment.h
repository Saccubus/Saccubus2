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

#ifndef CONTEXT_COMMENT_H_
#define CONTEXT_COMMENT_H_

#include <string>
#include <tr1/memory>
#include <tr1/functional>
#include "../../classdefs.h"
#include "../../util/ClassAccessor.h"

namespace nekomata{
namespace system{
class Comment;
}}
namespace saccubus {
namespace layer {
namespace item {

class Comment {
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
		Big=39,
		Small=15,
		Medium=24
	};
	enum PlaceX{
		Right,
		Center,
		Left
	};
	enum PlaceY{
		Top,
		Middle,
		Bottom,
	};
	DEF_ATTR_ACCESSOR(public, public, std::string, message);
	DEF_ATTR_ACCESSOR(public, public, const meta::Comment*, orig);
	DEF_ATTR_ACCESSOR(public, public, float, from);
	DEF_ATTR_ACCESSOR(public, public, float, to);
	DEF_ATTR_ACCESSOR(public, public, bool, isButton);
	DEF_ATTR_ACCESSOR(public, public, bool, isYourPost);
	DEF_ATTR_ACCESSOR(public, public, bool, fromButton);
	DEF_ATTR_ACCESSOR(public, public, bool, full);
	DEF_ATTR_ACCESSOR(public, public, bool, sage);
	DEF_ATTR_ACCESSOR(public, public, bool, patissier);
	DEF_ATTR_ACCESSOR(public, public, enum Device, device);
	DEF_ATTR_ACCESSOR(public, public, bool, visibility);
	DEF_ATTR_ACCESSOR(public, public, enum Size, size);
	DEF_ATTR_ACCESSOR(public, public, enum Layer, layer);
	DEF_ATTR_ACCESSOR(public, public, enum PlaceX, placeX);
	DEF_ATTR_ACCESSOR(public, public, enum PlaceY, placeY);
	DEF_ATTR_ACCESSOR(public, public, unsigned int, color);
	DEF_ATTR_ACCESSOR(public, public, unsigned int, shadowColor);
public:
	Comment();
	Comment(const meta::Comment* comment);
	virtual ~Comment();
private:
	void setDefault();
public:
	std::tr1::shared_ptr<nekomata::system::Comment> createNekomataComment();
};

}}}
#endif /* CONTEXT_COMMENT_H_ */
