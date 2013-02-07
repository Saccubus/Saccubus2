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
#include "../../mock/draw/Sprite.h"
#include "../../mock/draw/Renderer.h"
#include "../../../../saccubus/draw/cairo/Sprite.h"
#include "../../../../saccubus/draw/LayerdSprite.h"
using namespace saccubus::mock::draw;

namespace saccubus{
namespace test {
namespace draw{

TEST(SpriteHandlerTest, BasicTest)
{
	Renderer renderer(log_err);
	{
		Sprite::Handler<saccubus::draw::RawSprite> spr = renderer.queryRawSprite(100, 100);
		ASSERT_TRUE(spr); //boolに変換できる
		ASSERT_EQ(0U, renderer.availableRawSprites());
	}
	ASSERT_EQ(1U, renderer.availableRawSprites());
}

TEST(SpriteHandlerTest, FreeTest)
{
	Renderer renderer(log_err);
	{
		Sprite::Handler<saccubus::draw::RawSprite> spr = renderer.queryRawSprite(100, 100);
		ASSERT_EQ(0U, renderer.availableRawSprites());
	}
	ASSERT_EQ(1U, renderer.availableRawSprites());
}

TEST(SpriteHandlerTest, CopyTest)
{
	Renderer renderer(log_err);
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
	Renderer renderer(log_err);
	saccubus::mock::draw::Sprite* mockSprite = new mock::draw::Sprite(renderer.handler(), 0, 0);
	Sprite::Handler<saccubus::mock::draw::Sprite> spr(mockSprite);
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
	Renderer renderer(log_err);
	mock::draw::Sprite* mockSprite = new mock::draw::Sprite(renderer.handler(), 0, 0);
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

}}}

