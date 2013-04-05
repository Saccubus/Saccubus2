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

#include "Label.h"
#include "Comment.h"
#include "../../draw/CommentFactory.h"

namespace saccubus {
namespace layer {
namespace item {

Label::Label(nekomata::system::System& system, draw::CommentFactory* commentFactory)
: NekoItem(this), nekomata::system::Label(system)
{
	this->commentFactory(commentFactory);
}

void Label::onChanged()
{
	this->invalidate();
}
draw::Sprite::Handler<draw::Sprite> Label::createSprite(std::shared_ptr<saccubus::draw::Context> ctx)
{
	return this->commentFactory()->renderLabelText(ctx, this);
}

}}}
