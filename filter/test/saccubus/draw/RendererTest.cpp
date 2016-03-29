/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include "../../mock/draw/Sprite.h"
#include "../../mock/draw/Renderer.h"

namespace saccubus{
namespace draw{

TEST(RendererTest, BasicQueryTest)
{
	samock::draw::Renderer renderer(log_err);
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
		samock::draw::Renderer renderer(log_err);
		spr = renderer.queryRawSprite(10, 11);
		ASSERT_EQ(10, spr->width());
		ASSERT_EQ(11, spr->height());
	}
	// rendererは開放されてしまうが、Handlerは生きている
	ASSERT_EQ(10, spr->width());
	ASSERT_EQ(11, spr->height());
}

}}

