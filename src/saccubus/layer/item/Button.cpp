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
#include "../../draw/LayerdSprite.h"
#include "../../draw/CommentFactory.h"
#include "../../draw/ShapeFactory.h"

namespace saccubus {
namespace util {

Button::Button(draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory)
:Comment(commentFactory, shapeFactory)
{
	// TODO Auto-generated constructor stub

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

bool Button::isButton() const
{
	return true;
}

bool Button::onClick()
{
	return true;
}

draw::Sprite::Handler<draw::Sprite> Button::createSprite(std::tr1::shared_ptr<saccubus::draw::Context> ctx)
{
	draw::Sprite::Handler<draw::LayerdSprite> layerd = draw::LayerdSprite::newInstance();
	draw::Sprite::Handler<draw::Sprite> textSpr = this->commentFactory()->renderComment(ctx, this);
	draw::Sprite::Handler<draw::Sprite> btnSpr = this->shapeFactory()->renderButton(ctx, textSpr->width(), textSpr->height(), this->color());
	layerd->addSprite(0, 0, btnSpr);
	layerd->addSprite((btnSpr->width()-textSpr->width())/2, (btnSpr->height()-textSpr->height())/2, textSpr);
	return layerd;
}

}}
