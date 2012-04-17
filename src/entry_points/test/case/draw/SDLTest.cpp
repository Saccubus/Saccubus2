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

#include "../../TestCommon.h"
#include "../../../../saccubus/draw/sdl/Sprite.h"
#include "../../../../saccubus/draw/sdl/Renderer.h"
#include "../../../../saccubus/draw/sdl/SimpleCommentFactory.h"
#include "../../../../saccubus/layer/item/Comment.h"
#include "../../mock/meta/Comment.h"

using namespace saccubus::draw;
using namespace saccubus::layer::item;
using namespace saccubus::mock;

namespace saccubus{
namespace test {
namespace draw{

TEST(SDLTest, QureyTest)
{
	mock::meta::Comment orig = mock::meta::Comment();
	orig.message("おいしいうどんが食べたいな");
	orig.mail("big");
	layer::item::Comment comment = layer::item::Comment(&orig);
	sdl::Renderer renderer(log_err, 640, 480);
	sdl::SimpleCommentFactory factory(log_err, &renderer);

	Sprite::Handler<sdl::Sprite> spr, dspr;
	ASSERT_NO_THROW(spr = factory.renderComment(&comment, 1).cast<sdl::Sprite>());
	ASSERT_GT(spr->width(), 0);
	ASSERT_GT(spr->height(), 0);

	ASSERT_NO_THROW(dspr = factory.renderComment(&comment, 1.5).cast<sdl::Sprite>());

	//まあ大体2倍ならよし
	ASSERT_NEAR(spr->width() * 1.5, dspr->width(), dspr->width()/20.0f);
	ASSERT_NEAR(spr->height() * 1.5, dspr->height(), dspr->height()/20.0f);
}


}}}
