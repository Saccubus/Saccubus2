/*
 * VideoContext.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "../../TestCommon.h"
#include <fstream>
#include "../../../../saccubus/meta/VideoContext.h"
using namespace saccubus::meta;

TEST(VideoContextTest, ReadingTest)
{
	VideoContext ctx(log_err);
	std::vector<std::string> threads;
	threads.push_back(MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	ctx.init(MATERIAL_DIR"sm14097905_video_test.mp4",MATERIAL_DIR"sm14097905_meta_info.xml", MATERIAL_DIR"getflv.txt", threads);

	ASSERT_TRUE(ctx.metaInfo());
	ASSERT_TRUE(ctx.playInfo());
	ASSERT_EQ(1, ctx.threadSize());
	ASSERT_FALSE(ctx.threadBegin() == ctx.threadEnd());
	ASSERT_TRUE(ctx.hasThread(1302222473L));
}


