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

#if 0

#include "../../../TestCommon.h"
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../mock/meta/Comment.h"
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
	saccubus::mock::meta::Comment orig;
	orig.mail("invisible");
	{
		saccubus::layer::item::Comment* ctx = pipeLine->process(&orig);
		ASSERT_FALSE(ctx->visibility());
		delete ctx;
	}
}

TEST_F(CommentTest, MultiInterpretTest)
{
	saccubus::mock::meta::Comment orig;
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

