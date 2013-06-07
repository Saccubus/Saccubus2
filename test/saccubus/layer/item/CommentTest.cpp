/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#if 0

#include "../../../TestCommon.h"
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../mock/model/Comment.h"
using namespace saccubus::mock;

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class CommentTest : public ::testing::Test
{
protected:
	saccubus::layer::item::CommentPipeLine* pipeLine;
public:
	void SetUp(){
		pipeLine = new saccubus::layer::item::CommentPipeLine(log_err, 0, 0, 0, 0);
	}
	void TearDown(){
		delete pipeLine;
	}
};

TEST_F(CommentTest, InterpretTest)
{
	saccubus::mock::model::Comment orig;
	orig.mail("invisible");
	{
		saccubus::layer::item::Comment* ctx = pipeLine->process(&orig);
		ASSERT_FALSE(ctx->visibility());
		delete ctx;
	}
}

TEST_F(CommentTest, MultiInterpretTest)
{
	saccubus::mock::model::Comment orig;
	orig.mail("sage docomo");
	{
		saccubus::layer::item::Comment* ctx = pipeLine->process(&orig);
		ASSERT_TRUE(ctx->sage());
		ASSERT_EQ(saccubus::layer::item::Comment::docomo, ctx->device());
		delete ctx;
	}
}

}}}}

#endif

