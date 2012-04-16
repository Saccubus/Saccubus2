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
	saccubus::draw::Sprite* pspr;
	{
		Sprite::Handler<saccubus::draw::Sprite> spr = renderer.queryRawSprite(10, 11);
		ASSERT_EQ(10, spr->width());
		ASSERT_EQ(11, spr->height());
		pspr = spr.get();
	}
	//スプライトが返却されていることを確認
	ASSERT_EQ(1U, renderer.availableRawSprites());
	{
		Sprite::Handler<saccubus::draw::Sprite> spr = renderer.queryRawSprite(9, 10);
		ASSERT_EQ(9, spr->width());
		ASSERT_EQ(10, spr->height());
		ASSERT_EQ(pspr, spr.get());
	}
	ASSERT_EQ(1U, renderer.availableRawSprites());
}

TEST(RendererTest, AllocationTest)
{
	Sprite::Handler<saccubus::draw::Sprite> spr;
	{
		Renderer renderer;
		spr = renderer.queryRawSprite(10, 11);
		ASSERT_EQ(10, spr->width());
		ASSERT_EQ(11, spr->height());
	}
	// rendererは開放されてしまうが、Handlerは生きている
	ASSERT_EQ(10, spr->width());
	ASSERT_EQ(11, spr->height());
}

}}}

