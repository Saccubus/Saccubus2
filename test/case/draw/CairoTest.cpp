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

#if 0
#include <memory>
#include "../../TestCommon.h"
#include "../../../../saccubus/draw/cairo/Sprite.h"
#include "../../../../saccubus/draw/cairo/Renderer.h"
#include "../../../../saccubus/draw/cairo/Context.h"
#include "../../../../saccubus/draw/cairo/SimpleCommentFactory.h"
#include "../../../../saccubus/draw/cairo/SimpleShapeFactory.h"
#include "../../../../saccubus/layer/item/Comment.h"
#include "../../mock/meta/Comment.h"
#include "../../mock/MockSystem.h"

namespace saccubus{
namespace test {
namespace draw{

class CairoTest : public ::testing::Test
{
protected:
	saccubus::draw::cairo::Renderer* renderer;
	std::shared_ptr<saccubus::draw::Context> ctx;
	saccubus::draw::cairo::SimpleCommentFactory* commentFactory;
	saccubus::draw::cairo::SimpleShapeFactory* shapeFactory;
public:
	void SetUp(){
		renderer = new saccubus::draw::cairo::Renderer(log_err, std::map<std::string, std::string>());
		ctx=std::shared_ptr<saccubus::draw::Context>(renderer->createContext(saccubus::draw::Renderer::ARGB32, 0, 0, 0, 0));
		commentFactory = new saccubus::draw::cairo::SimpleCommentFactory(log_err, renderer, std::map<std::string, std::string>());
		shapeFactory = new saccubus::draw::cairo::SimpleShapeFactory(log_err, renderer, std::map<std::string, std::string>());
	}
	void TearDown(){
		delete shapeFactory;
		delete commentFactory;
		ctx.reset();
		delete renderer;
	}
};

TEST_F(CairoTest, QureyTest)
{
	layer::item::Comment comment = layer::item::Comment(commentFactory, shapeFactory);
	comment.message("おいしいうどんが食べたいな");
	comment.sizeType(saccubus::layer::item::Comment::Big);

	saccubus::draw::Sprite::Handler<saccubus::draw::cairo::Sprite> spr, dspr;
	ASSERT_NO_THROW(spr = comment.querySprite(ctx).cast<saccubus::draw::cairo::Sprite>());
	ASSERT_GT(spr->width(), 0);
	ASSERT_GT(spr->height(), 0);

	ASSERT_NO_THROW(dspr = commentFactory->renderComment(ctx, &comment).cast<saccubus::draw::cairo::Sprite>());
}

TEST_F(CairoTest, EmptyStringTest)
{
	layer::item::Comment comment = layer::item::Comment(commentFactory, shapeFactory);
	comment.message("");
	comment.sizeType(layer::item::Comment::Big);

	saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> spr;
	ASSERT_NO_THROW(spr = commentFactory->renderComment(ctx, &comment));
	ASSERT_EQ(0, spr->width());
	ASSERT_EQ(0, spr->height());
}

/*
TEST_F(CairoTest, ShapeTest)
{
	saccubus::draw::cairo::SimpleShapeFactory factory = saccubus::draw::cairo::SimpleShapeFactory(log_err, renderer);
	saccubus::mock::MockSystem mock = saccubus::mock::MockSystem();
	saccubus::layer::item::Shape shape = saccubus::layer::item::Shape(&mock, shapeFactory);
	shape.color(0xff0000);
	shape.width(15);
	shape.height(60);
	shape.alpha(0.5);
	shape.rotation(30);
	shape.shape("circle");
	saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> spr = shape.querySprite( ctx );

	ASSERT_EQ(15, spr->width());
	ASSERT_EQ(60, spr->height());
}*/

TEST_F(CairoTest, ButtonTest)
{
	saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> spr = shapeFactory->renderButton(ctx, 300, 100, 0xff0000);

	ASSERT_EQ(300, spr->width());
	ASSERT_EQ(100, spr->height());
}

}}}

#endif
