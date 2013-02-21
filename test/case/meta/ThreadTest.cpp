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
#include "../../../src/saccubus/meta/Thread.h"
#include "../../../src/saccubus/meta/Comment.h"
using namespace saccubus::meta;

namespace saccubus{
namespace test {
namespace meta {

TEST(ThreadTest, ThreadTest_ThradInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	ASSERT_EQ(1302222473LLU, th->thread());
	ASSERT_EQ(1333155993LLU, th->server_time());
	ASSERT_EQ(0x49eb1600LLU, th->ticket());
	ASSERT_EQ(1020U, th->size());
	delete th;
}

TEST(ThreadTest, ThreadTest_CommentInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	ASSERT_EQ(1020U, th->size());

	//begin
	const Comment* com = *th->begin();
	ASSERT_EQ(1302222473LLU, com->thread());
	ASSERT_TRUE(com->fork());
	ASSERT_FLOAT_EQ(0.0f, com->vpos());
	ASSERT_EQ(1LLU, com->no());
	ASSERT_EQ(1310831408LLU, com->date());

	//end
	com = *(th->end()-1);
	ASSERT_EQ(1302222473LLU, com->thread());
	ASSERT_EQ(100U, com->no());
	ASSERT_FLOAT_EQ(109.86f, com->vpos());
	ASSERT_EQ(1302637189LLU, com->date());
	ASSERT_TRUE(com->anonymity());
	delete th;
}

}}}
