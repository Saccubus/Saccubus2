/*
 * SpriteFactoryTest.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "mock/Sprite.h"
#include "mock/SpriteFactory.h"
using namespace saccubus::test::draw;

TEST(SpriteFactoryTest, BasicQueryTest)
{
	SpriteFactory factory;
	saccubus::draw::Sprite* spr;
	{
		Sprite::Handler handler = factory.querySprite(10, 11);
		ASSERT_EQ(10, handler->width());
		ASSERT_EQ(11, handler->height());
		spr = *handler;
	}
	//スプライトが返却されていることを確認
	ASSERT_EQ(1, factory.availableSprites());
	{
		Sprite::Handler handler = factory.querySprite(10, 10);
		ASSERT_EQ(10, handler->width());
		ASSERT_EQ(11, handler->height());
		ASSERT_EQ(spr, *handler);
	}
	ASSERT_EQ(1, factory.availableSprites());
}

TEST(SpriteFactoryTest, AllocationTest)
{
	Sprite::Handler handler;
	{
		SpriteFactory factory;
		handler = factory.querySprite(10, 11);
		ASSERT_EQ(10, handler->width());
		ASSERT_EQ(11, handler->height());
	}
	// factoryは開放されてしまうが、Handlerは生きている
	ASSERT_EQ(10, handler->width());
	ASSERT_EQ(11, handler->height());
}


