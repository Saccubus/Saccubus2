/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../../TestCommon.h"
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../nicomo/model/Comment.h"

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class CommentTest : public ::testing::Test
{
protected:
public:
	void SetUp(){
	}
	void TearDown(){
	}
};

TEST_F(CommentTest, InterpretTest)
{
	nicomock::model::Comment orig;
	orig.mail("invisible");
	saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
	ASSERT_FALSE(com.visibility());
}

TEST_F(CommentTest, MultiInterpretTest)
{
	nicomock::model::Comment orig;
	orig.mail("sage docomo");
	saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
	ASSERT_TRUE(com.sage());
	ASSERT_EQ(saccubus::layer::item::Comment::docomo, com.device());
}

}}}}

