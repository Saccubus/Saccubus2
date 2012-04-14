/*
 * Video.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "../../TestCommon.h"
#include <fstream>
#include "../../../../saccubus/meta/Video.h"
using namespace saccubus::meta;

namespace saccubus{
namespace test {
namespace meta {


TEST(VideoTest, ReadingTest)
{
	Video video(log_err);
	std::vector<std::string> threads;
	threads.push_back(MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	video.initVideoFile(MATERIAL_DIR"sm14097905_video_test.mp4");
	video.initMetaInfo(MATERIAL_DIR"sm14097905_meta_info.xml");
	video.initPlayInfo(MATERIAL_DIR"getflv.txt");
	video.initThread(threads);

	ASSERT_TRUE(video.metaInfo());
	ASSERT_TRUE(video.playInfo());
	ASSERT_EQ(1U, video.threadSize());
	ASSERT_FALSE(video.threadBegin() == video.threadEnd());
	ASSERT_TRUE(video.hasThread(1302222473L));
}

}}}
