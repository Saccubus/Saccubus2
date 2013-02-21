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
#include <nekomata/system/System.h>
#include "../../../../../saccubus/layer/item/Comment.h"
#include "../../../../../saccubus/layer/item/CommentPipeLine.h"
#include "../../../mock/meta/Comment.h"
#include "../../../mock/MockSystem.h"
using namespace saccubus::mock;
using nekomata::system::Replace;
using saccubus::layer::item::NekomataReplaceOperation;
using saccubus::layer::item::Comment;

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class NekomataReplaceOperationTest : public ::testing::Test
{
protected:
	mock::MockSystem mockSystem;
	Replace* replace;
	Comment* com;
public:
	void SetUp(){
		replace = new Replace(mockSystem);
		com = new Comment(0, 0);
	}
	void TearDown(){
		delete com;
		delete replace;
	}
};


TEST_F(NekomataReplaceOperationTest, BasicTest)
{
	replace->load("", "", true, "", true, true, 1, "", "");
	com->message("unchanged");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ(1U, com->color());
	ASSERT_EQ("unchanged", com->message());
}

TEST_F(NekomataReplaceOperationTest, SrcTest)
{
	replace->load("a", "b", true, "", true, true, 1, "", "");
	com->message("a");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("b", com->message());

	com->message("aaa");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("aaa", com->message());

	replace->load("a", "", true, "", false, true, 1, "", "");
	com->message("aaa");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("aaa", com->message());
	ASSERT_EQ(1U, com->color());

	replace->load("a", "b", true, "", true, false, 1, "", "");
	com->message("aaa");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("b", com->message());
	ASSERT_EQ(1U, com->color());
}

}}}}

#endif
