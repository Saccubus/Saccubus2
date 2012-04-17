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
#include "../../../../saccubus/context/Comment.h"
#include "../../mock/meta/Comment.h"
using namespace saccubus::mock;
using saccubus::context::Comment;

namespace saccubus{
namespace test {
namespace context{

class CommentCommandTest : public ::testing::Test
{
protected:
	saccubus::mock::meta::Comment meta;
	saccubus::context::Comment* ctx;
public:
	void SetUp(){
		this->ctx = new saccubus::context::Comment(log_err, &meta);
	}
	void TearDown(){
		delete ctx;
	}
};

TEST_F(CommentCommandTest, ColorTest)
{
	{
		ASSERT_TRUE(Comment::interpret("red", ctx));
		ASSERT_EQ(0xFF0000U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}

	{
		ASSERT_TRUE(Comment::interpret("black", ctx));
		ASSERT_EQ(0x000000U, ctx->color());
		ASSERT_EQ(0xFFFFFFU, ctx->shadowColor());
	}
}
TEST_F(CommentCommandTest, PremiumColorTest)
{
	meta.premium(true);
	{
		ASSERT_TRUE(Comment::interpret("purple2", ctx));
		ASSERT_EQ(0x6633CCU, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
	{
		ASSERT_TRUE(Comment::interpret("white2", ctx));
		ASSERT_EQ(0xCCCC99U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
	{
		ASSERT_TRUE(Comment::interpret("niconicowhite", ctx));
		ASSERT_EQ(0xCCCC99U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
}

TEST_F(CommentCommandTest, PermissionTest)
{
	meta.premium(false);
	ctx->color(0U);
	ctx->shadowColor(0U);
	{
		ASSERT_FALSE(Comment::interpret("purple2", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
	{
		ASSERT_FALSE(Comment::interpret("white2", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
	{
		ASSERT_FALSE(Comment::interpret("niconicowhite", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
	{
		ASSERT_FALSE(Comment::interpret("#123456", ctx));
		ASSERT_EQ(0x0U, ctx->color());
		ASSERT_EQ(0x0U, ctx->shadowColor());
	}
}

TEST_F(CommentCommandTest, PremiumColorCodeTest)
{
	meta.premium(true);
	{
		ASSERT_TRUE(Comment::interpret("#123456", ctx));
		ASSERT_EQ(0x123456U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
	{
		ASSERT_TRUE(Comment::interpret("#FFFFFF", ctx));
		ASSERT_EQ(0xFFFFFFU, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
}

TEST_F(CommentCommandTest, PlaceXTest)
{
	ASSERT_EQ(Comment::Center, ctx->placeX());
	//コメントからはいじれない。
}
TEST_F(CommentCommandTest, PlaceYTest)
{
	ASSERT_EQ(Comment::Middle, ctx->placeY());
	{
		ASSERT_TRUE(Comment::interpret("shita", ctx));
		ASSERT_EQ(Comment::Bottom, ctx->placeY());
	}
	{
		ASSERT_TRUE(Comment::interpret("ue", ctx));
		ASSERT_EQ(Comment::Top, ctx->placeY());
	}
	{
		ASSERT_TRUE(Comment::interpret("naka", ctx));
		ASSERT_EQ(Comment::Middle, ctx->placeY());
	}
}

TEST_F(CommentCommandTest, EtcTest)
{
	{
		ctx->full(false);
		ASSERT_FALSE(ctx->full());
		ASSERT_TRUE(Comment::interpret("full", ctx));
		ASSERT_TRUE(ctx->full());
	}
	{
		ctx->sage(false);
		ASSERT_FALSE(ctx->sage());
		ASSERT_TRUE(Comment::interpret("sage", ctx));
		ASSERT_TRUE(ctx->sage());
	}
	{
		ctx->patissier(false);
		ASSERT_FALSE(ctx->patissier());
		ASSERT_TRUE(Comment::interpret("patissier", ctx));
		ASSERT_TRUE(ctx->patissier());
	}
	{
		ctx->visibility(true);
		ASSERT_TRUE(ctx->visibility());
		ASSERT_TRUE(Comment::interpret("invisible", ctx));
		ASSERT_FALSE(ctx->visibility());
	}
	{
		ctx->fromButton(false);
		ASSERT_FALSE(ctx->fromButton());
		ASSERT_TRUE(Comment::interpret("from_button", ctx));
		ASSERT_TRUE(ctx->fromButton());
	}
	{
		ctx->isButton(false);
		ASSERT_FALSE(ctx->isButton());
		ASSERT_TRUE(Comment::interpret("is_button", ctx));
		ASSERT_TRUE(ctx->isButton());
	}
}

TEST_F(CommentCommandTest, BrokenCommandTest)
{
	meta.premium(true);
	ASSERT_TRUE(Comment::interpret("#123456", ctx));
	ASSERT_FALSE(Comment::interpret("#12ker3", ctx));
}

}}}

