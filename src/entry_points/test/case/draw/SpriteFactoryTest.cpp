/*
 * RendererTest.cpp
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../mock/draw/Sprite.h"
#include "../../mock/draw/Renderer.h"
using namespace saccubus::mock::draw;

namespace saccubus{
namespace test {
namespace draw{

TEST(RendererTest, BasicQueryTest)
{
	Renderer renderer;
	saccubus::draw::Sprite* spr;
	{
		Sprite::Handler handler = renderer.querySprite(10, 11);
		ASSERT_EQ(10, handler->width());
		ASSERT_EQ(11, handler->height());
		spr = *handler;
	}
	//スプライトが返却されていることを確認
	ASSERT_EQ(1U, renderer.availableSprites());
	{
		Sprite::Handler handler = renderer.querySprite(9, 10);
		ASSERT_EQ(9, handler->width());
		ASSERT_EQ(10, handler->height());
		ASSERT_EQ(spr, *handler);
	}
	ASSERT_EQ(1U, renderer.availableSprites());
}

TEST(RendererTest, AllocationTest)
{
	Sprite::Handler handler;
	{
		Renderer renderer;
		handler = renderer.querySprite(10, 11);
		ASSERT_EQ(10, handler->width());
		ASSERT_EQ(11, handler->height());
	}
	// rendererは開放されてしまうが、Handlerは生きている
	ASSERT_EQ(10, handler->width());
	ASSERT_EQ(11, handler->height());
}

}}}

