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
#include "../../../src/saccubus/draw/LayerdSprite.h"

using saccubus::draw::LayerdSprite;
namespace saccubus{
namespace draw{

TEST(LayerdSpriteTest, BasicTest)
{
	samock::draw::Renderer renderer(log_err);
	{
		Sprite::Handler<LayerdSprite> layer = LayerdSprite::newInstance();
		layer->addSprite(0, 0, renderer.queryRawSprite(10, 12));
		ASSERT_EQ(10, layer->width());
		ASSERT_EQ(12, layer->height());
		ASSERT_EQ(0U, renderer.availableRawSprites());

		layer->addSprite(5, 5, renderer.queryRawSprite(3, 3));
		ASSERT_EQ(10, layer->width());
		ASSERT_EQ(12, layer->height());
		ASSERT_EQ(0U, renderer.availableRawSprites());

		layer->addSprite(10, 10, renderer.queryRawSprite(11, 13));
		ASSERT_EQ(21, layer->width());
		ASSERT_EQ(23, layer->height());
		ASSERT_EQ(0U, renderer.availableRawSprites());
	}

	ASSERT_EQ(3U, renderer.availableRawSprites());
}

TEST(LayerdSpriteTest, ShrinkTest)
{
	samock::draw::Renderer renderer(log_err);
	{
		Sprite::Handler<LayerdSprite> layer = LayerdSprite::newInstance();
		Sprite::Handler<saccubus::draw::RawSprite> spr1 = renderer.queryRawSprite(10, 12);
		layer->addSprite(0, 0, spr1);
		ASSERT_EQ(10, layer->width());
		ASSERT_EQ(12, layer->height());
		spr1->resize(5, 6);
		ASSERT_EQ(5, layer->width());
		ASSERT_EQ(6, layer->height());

		Sprite::Handler<saccubus::draw::RawSprite> spr2 = renderer.queryRawSprite(3, 4);
		layer->addSprite(5, 6, spr2);
		ASSERT_EQ(8, layer->width());
		ASSERT_EQ(10, layer->height());

		spr2->resize(2,3);
		ASSERT_EQ(7, layer->width());
		ASSERT_EQ(9, layer->height());
	}
}
}}
