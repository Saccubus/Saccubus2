/*
 * VideoContextTest.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/logging/Logger.h"
#include "../../../../saccubus/meta/Video.h"
#include "../../../../saccubus/context/Thread.h"
#include "../../../../saccubus/context/Video.h"
#include "../../../../saccubus/python/PyBridge.h"
#include <sstream>
using namespace saccubus;

namespace saccubus{
namespace test {
namespace context{

class Context_VideoTest : public ::testing::Test{
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

TEST_F(Context_VideoTest, BasicTest)
{
	saccubus::context::Video* ctx = new saccubus::context::Video(bridge, video);
	ASSERT_EQ(1U, ctx->threadSize());
	delete ctx;
}

}}}
