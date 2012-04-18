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


#include "../../../TestCommon.h"
#include "../../../../../saccubus/layer/item/Comment.h"
#include "../../../../../saccubus/layer/item/CommentPipeLine.h"
#include "../../../mock/meta/Comment.h"
using namespace saccubus::mock;
using saccubus::layer::item::MailOperation;
using saccubus::layer::item::Comment;

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class MailOperationTest : public ::testing::Test
{
protected:
	saccubus::mock::meta::Comment meta;
	saccubus::layer::item::Comment* ctx;
public:
	void SetUp(){
		this->ctx = new saccubus::layer::item::Comment(&meta);
	}
	void TearDown(){
		delete ctx;
	}
};

TEST_F(MailOperationTest, ColorTest)
{
	{
		ASSERT_TRUE(MailOperation::apply("red", ctx));
		ASSERT_EQ(0xFF0000U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}

	{
		ASSERT_TRUE(MailOperation::apply("black", ctx));
		ASSERT_EQ(0x000000U, ctx->color());
		ASSERT_EQ(0xFFFFFFU, ctx->shadowColor());
	}
}
TEST_F(MailOperationTest, PremiumColorTest)
{
	meta.premium(true);
	{
		ASSERT_TRUE(MailOperation::apply("purple2", ctx));
		ASSERT_EQ(0x6633CCU, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
	{
		ASSERT_TRUE(MailOperation::apply("white2", ctx));
		ASSERT_EQ(0xCCCC99U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
	{
		ASSERT_TRUE(MailOperation::apply("niconicowhite", ctx));
		ASSERT_EQ(0xCCCC99U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
}

TEST_F(MailOperationTest, PermissionTest)
{
	meta.premium(false);
	ctx->color(0U);
	ctx->shadowColor(0U);
	{
		ASSERT_FALSE(MailOperation::apply("purple2", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
	{
		ASSERT_FALSE(MailOperation::apply("white2", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
	{
		ASSERT_FALSE(MailOperation::apply("niconicowhite", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
	{
		ASSERT_FALSE(MailOperation::apply("#123456", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
}

TEST_F(MailOperationTest, PremiumColorCodeTest)
{
	meta.premium(true);
	{
		ASSERT_TRUE(MailOperation::apply("#123456", ctx));
		ASSERT_EQ(0x123456U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
	{
		ASSERT_TRUE(MailOperation::apply("#FFFFFF", ctx));
		ASSERT_EQ(0xFFFFFFU, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
}

TEST_F(MailOperationTest, PlaceXTest)
{
	ASSERT_EQ(Comment::Center, ctx->placeX());
	{
		this->ctx->layer(Comment::Normal);
		ASSERT_FALSE(MailOperation::apply("migi", ctx)); //投稿者コメントでないので失敗
		ASSERT_EQ(Comment::Center, ctx->placeX());
	}
	{
		this->ctx->layer(Comment::Forked);
		ASSERT_TRUE(MailOperation::apply("migi", ctx)); //投稿者コメントなので成功
		ASSERT_EQ(Comment::Right, ctx->placeX());
	}

}
TEST_F(MailOperationTest, PlaceYTest)
{
	ASSERT_EQ(Comment::Middle, ctx->placeY());
	{
		ASSERT_TRUE(MailOperation::apply("shita", ctx));
		ASSERT_EQ(Comment::Bottom, ctx->placeY());
	}
	{
		ASSERT_TRUE(MailOperation::apply("ue", ctx));
		ASSERT_EQ(Comment::Top, ctx->placeY());
	}
	{
		ASSERT_TRUE(MailOperation::apply("naka", ctx));
		ASSERT_EQ(Comment::Middle, ctx->placeY());
	}
}

TEST_F(MailOperationTest, EtcTest)
{
	{
		ctx->full(false);
		ASSERT_FALSE(ctx->full());
		ASSERT_TRUE(MailOperation::apply("full", ctx));
		ASSERT_TRUE(ctx->full());
	}
	{
		ctx->sage(false);
		ASSERT_FALSE(ctx->sage());
		ASSERT_TRUE(MailOperation::apply("sage", ctx));
		ASSERT_TRUE(ctx->sage());
	}
	{
		ctx->patissier(false);
		ASSERT_FALSE(ctx->patissier());
		ASSERT_TRUE(MailOperation::apply("patissier", ctx));
		ASSERT_TRUE(ctx->patissier());
	}
	{
		ctx->visibility(true);
		ASSERT_TRUE(ctx->visibility());
		ASSERT_TRUE(MailOperation::apply("invisible", ctx));
		ASSERT_FALSE(ctx->visibility());
	}
	{
		ctx->fromButton(false);
		ASSERT_FALSE(ctx->fromButton());
		ASSERT_TRUE(MailOperation::apply("from_button", ctx));
		ASSERT_TRUE(ctx->fromButton());
	}
	{
		ctx->isButton(false);
		ASSERT_FALSE(ctx->isButton());
		ASSERT_TRUE(MailOperation::apply("is_button", ctx));
		ASSERT_TRUE(ctx->isButton());
	}
}

TEST_F(MailOperationTest, BrokenCommandTest)
{
	meta.premium(true);
	ASSERT_TRUE(MailOperation::apply("#123456", ctx));
	ASSERT_FALSE(MailOperation::apply("#12ker3", ctx));
}

}}}}
