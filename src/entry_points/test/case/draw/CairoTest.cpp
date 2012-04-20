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
#include "../../../../saccubus/draw/cairo/Sprite.h"
#include "../../../../saccubus/draw/cairo/Renderer.h"
#include "../../../../saccubus/draw/cairo/SimpleCommentFactory.h"
#include "../../../../saccubus/draw/cairo/SimpleShapeFactory.h"
#include "../../../../saccubus/layer/item/Comment.h"
#include "../../../../saccubus/layer/item/Shape.h"
#include "../../mock/meta/Comment.h"
#include "../../mock/MockSystem.h"

using namespace saccubus::draw;
using namespace saccubus::layer::item;
using namespace saccubus::mock;

namespace saccubus{
namespace test {
namespace draw{

TEST(CairoTest, QureyTest)
{
	mock::draw::Context ctx;
	mock::meta::Comment orig = mock::meta::Comment();
	orig.message("おいしいうどんが食べたいな");
	orig.mail("big");
	layer::item::Comment comment = layer::item::Comment(&orig, 0, 0);
	cairo::Renderer renderer(log_err);
	cairo::SimpleCommentFactory factory(log_err, &renderer);

	Sprite::Handler<cairo::Sprite> spr, dspr;
	ASSERT_NO_THROW(spr = factory.renderComment(&comment, 1).cast<cairo::Sprite>());
	ASSERT_GT(spr->width(), 0);
	ASSERT_GT(spr->height(), 0);

	ASSERT_NO_THROW(dspr = factory.renderComment(&comment, 1.5).cast<cairo::Sprite>());

	//まあ大体2倍ならよし
	ASSERT_NEAR(spr->width() * 1.5, dspr->width(), dspr->width()/20.0f);
	ASSERT_NEAR(spr->height() * 1.5, dspr->height(), dspr->height()/20.0f);
}

TEST(CairoTest, EmptyStringTest)
{
	mock::draw::Context ctx;
	mock::meta::Comment orig = mock::meta::Comment();
	orig.message("");
	orig.mail("big");
	layer::item::Comment comment = layer::item::Comment(&orig, 0, 0);
	cairo::Renderer renderer(log_err);
	cairo::SimpleCommentFactory factory(log_err, &renderer);

	Sprite::Handler<saccubus::draw::Sprite> spr;
	ASSERT_NO_THROW(spr = factory.renderComment(&comment, 1));
	ASSERT_EQ(0, spr->width());
	ASSERT_EQ(0, spr->height());
}

TEST(CairoTest, ShapeTest)
{
	mock::draw::Context ctx;
	cairo::Renderer renderer(log_err);
	cairo::SimpleShapeFactory factory = cairo::SimpleShapeFactory(log_err, &renderer);
	MockSystem mock = MockSystem();
	Shape shape = Shape(renderer.createContext(), &mock, 0);
	shape.color(0xff0000);
	shape.width(15);
	shape.height(60);
	shape.alpha(0.5);
	shape.rotation(30);
	shape.shape("circle");
	Sprite::Handler<saccubus::draw::Sprite> spr = shape.querySprite(renderer.createContext());

	ASSERT_EQ(15, spr->width());
	ASSERT_EQ(60, spr->height());
}

TEST(CairoTest, ButtonTest)
{
	mock::draw::Context ctx;
	cairo::Renderer renderer(log_err);
	cairo::SimpleShapeFactory factory = cairo::SimpleShapeFactory(log_err, &renderer);
	Sprite::Handler<saccubus::draw::Sprite> spr = factory.renderButton(&ctx, 300, 100, 0xff0000);

	ASSERT_EQ(300, spr->width());
	ASSERT_EQ(100, spr->height());
}

}}}
