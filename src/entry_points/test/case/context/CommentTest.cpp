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

namespace saccubus{
namespace test {
namespace context{

TEST(CommentTest, InterpretTest)
{
	saccubus::mock::meta::Comment orig;
	orig.mail("invisible");
	{
		saccubus::context::Comment ctx = saccubus::context::Comment(&orig);
		ASSERT_FALSE(ctx.visibility());
	}
}

TEST(CommentTest, MultiInterpretTest)
{
	saccubus::mock::meta::Comment orig;
	orig.mail("sage docomo");
	{
		saccubus::context::Comment ctx = saccubus::context::Comment(&orig);
		ASSERT_TRUE(ctx.sage());
		ASSERT_EQ(saccubus::context::Comment::docomo, ctx.device());
	}
}
}}}


