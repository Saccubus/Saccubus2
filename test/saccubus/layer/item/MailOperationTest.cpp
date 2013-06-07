/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#if 0

#include "../../../TestCommon.h"
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../../src/saccubus/layer/item/CommentPipeLine.h"
#include "../../../mock/model/Comment.h"
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
	saccubus::layer::item::Comment* com;
public:
	void SetUp(){
		this->com = new saccubus::layer::item::Comment(0, 0);
	}
	void TearDown(){
		delete com;
	}
};

TEST_F(MailOperationTest, ColorTest)
{
	{
		ASSERT_TRUE(MailOperation::apply("red", com));
		ASSERT_EQ(0xFF0000U, com->color());
		ASSERT_EQ(0x000000U, com->shadowColor());
	}

	{
		ASSERT_TRUE(MailOperation::apply("black", com));
		ASSERT_EQ(0x000000U, com->color());
		ASSERT_EQ(0xFFFFFFU, com->shadowColor());
	}
}
TEST_F(MailOperationTest, PremiumColorTest)
{
	com->isPremium(true);
	{
		ASSERT_TRUE(MailOperation::apply("purple2", com));
		ASSERT_EQ(0x6633CCU, com->color());
		ASSERT_EQ(0x000000U, com->shadowColor());
	}
	{
		ASSERT_TRUE(MailOperation::apply("white2", com));
		ASSERT_EQ(0xCCCC99U, com->color());
		ASSERT_EQ(0x000000U, com->shadowColor());
	}
	{
		ASSERT_TRUE(MailOperation::apply("niconicowhite", com));
		ASSERT_EQ(0xCCCC99U, com->color());
		ASSERT_EQ(0x000000U, com->shadowColor());
	}
}

TEST_F(MailOperationTest, PermissionTest)
{
	com->isPremium(false);
	com->color(0U);
	com->shadowColor(0U);
	{
		ASSERT_FALSE(MailOperation::apply("purple2", com));
		ASSERT_EQ(0x0U, com->color());
		ASSERT_EQ(0x0U, com->shadowColor());
	}
	{
		ASSERT_FALSE(MailOperation::apply("white2", com));
		ASSERT_EQ(0x0U, com->color());
		ASSERT_EQ(0x0U, com->shadowColor());
	}
	{
		ASSERT_FALSE(MailOperation::apply("niconicowhite", com));
		ASSERT_EQ(0x0U, com->color());
		ASSERT_EQ(0x0U, com->shadowColor());
	}
	{
		ASSERT_FALSE(MailOperation::apply("#123456", com));
		ASSERT_EQ(0x0U, com->color());
		ASSERT_EQ(0x0U, com->shadowColor());
	}
}

TEST_F(MailOperationTest, PremiumColorCodeTest)
{
	com->isPremium(true);
	{
		ASSERT_TRUE(MailOperation::apply("#123456", com));
		ASSERT_EQ(0x123456U, com->color());
		ASSERT_EQ(0x000000U, com->shadowColor());
	}
	{
		ASSERT_TRUE(MailOperation::apply("#FFFFFF", com));
		ASSERT_EQ(0xFFFFFFU, com->color());
		ASSERT_EQ(0x000000U, com->shadowColor());
	}
}

TEST_F(MailOperationTest, PlaceYTest)
{
	ASSERT_EQ(Comment::Middle, com->placeY());
	{
		ASSERT_TRUE(MailOperation::apply("shita", com));
		ASSERT_EQ(Comment::Bottom, com->placeY());
	}
	{
		ASSERT_TRUE(MailOperation::apply("ue", com));
		ASSERT_EQ(Comment::Top, com->placeY());
	}
	{
		ASSERT_TRUE(MailOperation::apply("naka", com));
		ASSERT_EQ(Comment::Middle, com->placeY());
	}
}

TEST_F(MailOperationTest, TimeTest)
{
	{
		com->vpos(0);
		com->from(0);
		com->to(0);
		com->layer(Comment::Forked);
		ASSERT_TRUE(MailOperation::apply("@10", com));
		ASSERT_FLOAT_EQ(10.0, com->to()-com->from());

	}
}

TEST_F(MailOperationTest, EtcTest)
{
	{
		com->full(false);
		ASSERT_FALSE(com->full());
		ASSERT_TRUE(MailOperation::apply("full", com));
		ASSERT_TRUE(com->full());
	}
	{
		com->sage(false);
		ASSERT_FALSE(com->sage());
		ASSERT_TRUE(MailOperation::apply("sage", com));
		ASSERT_TRUE(com->sage());
	}
	{
		com->patissier(false);
		ASSERT_FALSE(com->patissier());
		ASSERT_TRUE(MailOperation::apply("patissier", com));
		ASSERT_TRUE(com->patissier());
	}
	{
		com->visibility(true);
		ASSERT_TRUE(com->visibility());
		ASSERT_TRUE(MailOperation::apply("invisible", com));
		ASSERT_FALSE(com->visibility());
	}
	{
		com->fromButton(false);
		ASSERT_FALSE(com->fromButton());
		ASSERT_TRUE(MailOperation::apply("from_button", com));
		ASSERT_TRUE(com->fromButton());
	}
}

TEST_F(MailOperationTest, BrokenCommandTest)
{
	com->isPremium(true);
	ASSERT_TRUE(MailOperation::apply("#123456", com));
	ASSERT_FALSE(MailOperation::apply("#12ker3", com));
}

}}}}

#endif
