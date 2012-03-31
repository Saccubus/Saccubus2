/*
 * ThreadTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/meta/Thread.h"
#include "../../../../saccubus/meta/Comment.h"
using namespace saccubus::meta;

TEST(ThreadTest, ThreadTest_ThradInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	ASSERT_EQ(1302222473, th->thread());
	ASSERT_EQ(1333155993, th->server_time());
	ASSERT_EQ(0x49eb1600, th->ticket());
	delete th;
}

TEST(ThreadTest, ThreadTest_CommentInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	ASSERT_EQ(1020, th->size());

	//begin
	const Comment* com = *th->begin();
	ASSERT_EQ(1302222473, com->thread());
	ASSERT_TRUE(com->fork());
	ASSERT_FLOAT_EQ(0, com->vpos());
	ASSERT_EQ(0, com->mailSize());
	ASSERT_EQ(1, com->no());
	ASSERT_EQ(1310831408, com->date());

	//end
	com = *(th->end()-1);
	ASSERT_EQ(1302222473, com->thread());
	ASSERT_EQ(100, com->no());
	ASSERT_FLOAT_EQ(109.86, com->vpos());
	ASSERT_EQ(1302637189, com->date());
	ASSERT_EQ(1, com->mailSize());
	ASSERT_STREQ("184", com->mailBegin()->c_str());
	delete th;
}

