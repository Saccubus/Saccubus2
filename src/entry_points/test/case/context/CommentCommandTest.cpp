/*
 * CommentCommandTest.cpp
 *
 *  Created on: 2012/04/15
 *      Author: psi
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
		this->ctx = new saccubus::context::Comment(&meta);
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

TEST_F(CommentCommandTest, ColorCodeTest)
{
	meta.premium(true);
	{
		ASSERT_TRUE(Comment::interpret("#123456", ctx));
		ASSERT_EQ(0x123456U, ctx->color());
		ASSERT_EQ(0x000000U, ctx->shadowColor());
	}
}

}}}

