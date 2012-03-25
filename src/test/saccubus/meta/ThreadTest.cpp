/*
 * ThreadTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../saccubus/meta/Thread.h"
#include "../../../saccubus/meta/Chat.h"
using namespace saccubus::meta;

TEST(ThreadTest, UserThreadTest_ThradInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"thread_sample.xml");
	ASSERT_EQ(1302222473, th->thread());
	ASSERT_EQ(1332577322, th->server_time());
	ASSERT_EQ(0x581a3600, th->ticket());
	delete th;
}

TEST(ThreadTest, UserThreadTest_ChatInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"thread_sample.xml");
	ASSERT_EQ(120, th->size());

	//begin
	const Chat* chat = *th->begin();
	ASSERT_EQ(1302222473, chat->thread());
	ASSERT_EQ(1, chat->no());
	ASSERT_FLOAT_EQ(45.43, chat->vpos());
	ASSERT_EQ(1302222847, chat->date());
	ASSERT_EQ(1, chat->mailSize());
	ASSERT_STREQ("184", chat->mailBegin()->c_str());

	//end
	chat = *(th->end()-1);
	ASSERT_EQ(1302222473, chat->thread());
	ASSERT_EQ(120, chat->no());
	ASSERT_FLOAT_EQ(49.10, chat->vpos());
	ASSERT_EQ(1320394574, chat->date());
	ASSERT_EQ(1, chat->mailSize());
	ASSERT_STREQ("184", chat->mailBegin()->c_str());
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

TEST(ThreadTest, OwnerThreadTest_ChatInfo)
{
	Thread* th = new Thread(log_err, MATERIAL_DIR"owner_thread_sample.xml");
	ASSERT_EQ(900, th->size());

	//begin
	const Chat* chat = *th->begin();
	ASSERT_EQ(1302222473, chat->thread());
	ASSERT_EQ(1, chat->no());
	ASSERT_FLOAT_EQ(0, chat->vpos());
	ASSERT_EQ(1310831408, chat->date());
	ASSERT_TRUE(chat->premium());
	ASSERT_EQ(0, chat->mailSize());

	//end
	chat = *(th->end()-1);
	ASSERT_EQ(1302222473, chat->thread());
	ASSERT_EQ(900, chat->no());
	ASSERT_FLOAT_EQ(0, chat->vpos());
	ASSERT_EQ(1310831408, chat->date());
	ASSERT_TRUE(chat->premium());
	ASSERT_EQ(0, chat->mailSize());
	delete th;
}
