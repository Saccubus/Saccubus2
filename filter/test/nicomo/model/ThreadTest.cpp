/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include <nicomo/model/Thread.h>
#include <nicomo/model/Comment.h>

namespace nicomo {
namespace model {

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

}}
