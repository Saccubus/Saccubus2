/*
 * ThreadTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../saccubus/meta/Thread.h"
#include "../../../saccubus/meta/Comment.h"
using namespace saccubus::meta;

TEST(ThreadTest, UserThreadTest_ThradInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"thread_sample.xml");
	ASSERT_EQ(1302222473, th->thread());
	ASSERT_EQ(1332577322, th->server_time());
	ASSERT_EQ(0x581a3600, th->ticket());
	delete th;
}

TEST(ThreadTest, UserThreadTest_CommentInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"thread_sample.xml");
	ASSERT_EQ(120, th->size());

	//begin
	const Comment* com = *th->begin();
	ASSERT_EQ(1302222473, com->thread());
	ASSERT_EQ(1, com->no());
	ASSERT_FLOAT_EQ(45.43, com->vpos());
	ASSERT_EQ(1302222847, com->date());
	ASSERT_EQ(1, com->mailSize());
	ASSERT_STREQ("184", com->mailBegin()->c_str());

	//end
	com = *(th->end()-1);
	ASSERT_EQ(1302222473, com->thread());
	ASSERT_EQ(120, com->no());
	ASSERT_FLOAT_EQ(49.10, com->vpos());
	ASSERT_EQ(1320394574, com->date());
	ASSERT_EQ(1, com->mailSize());
	ASSERT_STREQ("184", com->mailBegin()->c_str());
	delete th;
}


TEST(ThreadTest, OwnerThreadTest_ThreadInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"owner_thread_sample.xml");
	ASSERT_EQ(1302222473, th->thread());
	ASSERT_EQ(1332577325, th->server_time());
	ASSERT_EQ(1310831408, th->ticket());
	delete th;
}

TEST(ThreadTest, OwnerThreadTest_CommentInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"owner_thread_sample.xml");
	ASSERT_EQ(900, th->size());

	//begin
	const Comment* com = *th->begin();
	ASSERT_EQ(1302222473, com->thread());
	ASSERT_EQ(1, com->no());
	ASSERT_FLOAT_EQ(0, com->vpos());
	ASSERT_EQ(1310831408, com->date());
	ASSERT_TRUE(com->premium());
	ASSERT_EQ(0, com->mailSize());

	//end
	com = *(th->end()-1);
	ASSERT_EQ(1302222473, com->thread());
	ASSERT_EQ(900, com->no());
	ASSERT_FLOAT_EQ(0, com->vpos());
	ASSERT_EQ(1310831408, com->date());
	ASSERT_TRUE(com->premium());
	ASSERT_EQ(0, com->mailSize());
	delete th;
}
