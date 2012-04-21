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

#ifndef Saccubus_LABEL_H__CPP_
#define Saccubus_LABEL_H__CPP_

#include <nekomata/system/System.h>
#include "NekoItem.h"
#include "Comment.h"

namespace saccubus {
namespace layer {
namespace item {

class Label: public saccubus::layer::item::NekoItem, public nekomata::system::Label {
	DEF_ATTR_ACCESSOR(private, private, draw::CommentFactory*, commentFactory);
private:
	Comment rendererdText;
public:
	explicit Label(nekomata::system::System& system, draw::CommentFactory* commentFactory);
	virtual ~Label();
	virtual void onChanged();
protected:
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx);
};

}}}
#endif /* INCLUDE_GUARD */
