/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <memory>
#include "../../TestCommon.h"
#include "../../../src/saccubus/draw/cairo/Sprite.h"
#include "../../../src/saccubus/draw/cairo/Renderer.h"
#include "../../../src/saccubus/draw/cairo/Context.h"
#include "../../../src/saccubus/draw/cairo/SimpleCommentFactory.h"
#include "../../../src/saccubus/draw/cairo/SimpleShapeFactory.h"
#include "../../../src/saccubus/layer/item/Comment.h"
#include "../../nicomo/model/Comment.h"
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
		ctx=std::shared_ptr<saccubus::draw::Context>(renderer->createContext(saccubus::draw::Renderer::ARGB32, nullptr, nico::ScreenHeight, nico::ScreenHeight, nico::ScreenHeight*4));
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
	nicomock::model::Comment orig;
	orig.message(std::string(u8"あいうえお、かきくけこ。"));
	orig.mail("big");
	layer::item::Comment comment ( commentFactory, shapeFactory, nullptr, &orig);

	ASSERT_GT(comment.width(ctx), 5);
	ASSERT_GT(comment.height(ctx), 5);

	ASSERT_NO_THROW(commentFactory->renderCommentText(ctx, &comment).cast<saccubus::draw::cairo::Sprite>());
}

TEST_F(CairoTest, EmptyStringTest)
{
	nicomock::model::Comment orig;
	orig.message("");
	orig.mail("big");
	layer::item::Comment comment ( commentFactory, shapeFactory, nullptr, &orig);

	ASSERT_LT(comment.width(ctx), 10);
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
