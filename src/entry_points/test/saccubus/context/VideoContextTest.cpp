/*
 * VideoContextTest.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/logging/Logger.h"
#include "../../../../saccubus/meta/Video.h"
#include "../../../../saccubus/context/ThreadContext.h"
#include "../../../../saccubus/context/VideoContext.h"
#include "../../../../saccubus/python/PyBridge.h"
#include <sstream>
using namespace saccubus;

class VideoContextTest : public ::testing::Test{
protected:
	python::PyBridge* bridge;
	meta::Video* video;
public:
	void SetUp(){
		bridge = new python::PyBridge(log_err);
		std::vector<std::string> threads;
		threads.push_back(MATERIAL_DIR"sm14097905_thread_1302222473.xml");
		video = new meta::Video(log_err);
		video->initPlayInfo(MATERIAL_DIR"getflv.txt");
		video->initMetaInfo(MATERIAL_DIR"sm14097905_meta_info.xml");
		video->initThread(threads);
		video->initVideoFile(MATERIAL_DIR"sm14097905_video_test.mp4");

	}
	void TearDown(){
		delete bridge;
		delete video;
	}
};

TEST_F(VideoContextTest, BasicTest)
{
	context::VideoContext* ctx = new context::VideoContext(bridge, video);
	ASSERT_EQ(1U, ctx->threadSize());
	delete ctx;
}
