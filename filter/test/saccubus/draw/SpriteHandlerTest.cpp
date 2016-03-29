/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include "../../mock/draw/Sprite.h"
#include "../../mock/draw/Renderer.h"
#include "../../../src/saccubus/draw/cairo/Sprite.h"
#include "../../../src/saccubus/draw/LayerdSprite.h"

namespace saccubus{
namespace draw{

TEST(SpriteHandlerTest, BasicTest)
{
	samock::draw::Renderer renderer(log_err);
	{
		Sprite::Handler<saccubus::draw::RawSprite> spr = renderer.queryRawSprite(100, 100);
		ASSERT_TRUE(spr); //boolに変換できる
		ASSERT_EQ(0U, renderer.availableRawSprites());
	}
	ASSERT_EQ(1U, renderer.availableRawSprites());
}

TEST(SpriteHandlerTest, FreeTest)
{
	samock::draw::Renderer renderer(log_err);
	{
		Sprite::Handler<saccubus::draw::RawSprite> spr = renderer.queryRawSprite(100, 100);
		ASSERT_EQ(0U, renderer.availableRawSprites());
	}
	ASSERT_EQ(1U, renderer.availableRawSprites());
}

TEST(SpriteHandlerTest, CopyTest)
{
	samock::draw::Renderer renderer(log_err);
	Sprite::Handler<saccubus::draw::RawSprite> spr2;
	{
		Sprite::Handler<saccubus::draw::RawSprite> spr = renderer.queryRawSprite(100, 100);
		spr2=spr;
		ASSERT_TRUE(spr);
		ASSERT_TRUE(spr2);
		ASSERT_EQ(spr.get(), spr2.get());
	}
	ASSERT_TRUE(spr2);
}

TEST(SpriteHandlerTest, StaticCastTest)
{
	samock::draw::Renderer renderer(log_err);
	samock::draw::Sprite* mockSprite = new samock::draw::Sprite(renderer.handler(), 0, 0);
	Sprite::Handler<samock::draw::Sprite> spr(mockSprite);
	ASSERT_TRUE(spr);
	ASSERT_TRUE(spr.get());
	ASSERT_EQ(mockSprite, spr.get());

	Sprite::Handler<saccubus::draw::RawSprite> rawSpr = spr;
	Sprite::Handler<saccubus::draw::RawSprite> rawSpr2;
	ASSERT_TRUE(rawSpr);
	ASSERT_TRUE(rawSpr.get());

	rawSpr2 = spr;
	ASSERT_TRUE(rawSpr2);
	ASSERT_TRUE(rawSpr2.get());

	Sprite::Handler<saccubus::draw::Sprite> baseSpr = rawSpr;
	Sprite::Handler<saccubus::draw::Sprite> baseSpr2;
	ASSERT_TRUE(baseSpr);
	ASSERT_TRUE(baseSpr.get());

	baseSpr2 = rawSpr;
	ASSERT_TRUE(baseSpr2);
	ASSERT_TRUE(baseSpr2.get());
}

TEST(SpriteHandlerTest, DynamicCastTest)
{
	samock::draw::Renderer renderer(log_err);
	samock::draw::Sprite* mockSprite = new samock::draw::Sprite(renderer.handler(), 0, 0);
	Sprite::Handler<saccubus::draw::Sprite> spr(mockSprite);

	Sprite::Handler<saccubus::draw::RawSprite> rawSpr = spr.cast<saccubus::draw::RawSprite>();
	Sprite::Handler<saccubus::draw::RawSprite> rawSpr2;
	ASSERT_TRUE(rawSpr);
	ASSERT_TRUE(rawSpr.get());

	rawSpr2 = spr.cast<saccubus::draw::RawSprite>();
	ASSERT_TRUE(rawSpr2);
	ASSERT_TRUE(rawSpr2.get());

	//失敗する例も試す
	ASSERT_THROW(spr.cast<saccubus::draw::cairo::Sprite>(), logging::Exception);
	ASSERT_THROW(spr.cast<saccubus::draw::LayerdSprite>(), logging::Exception);
}

}}

