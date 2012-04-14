/*
 * ThreadContextTest.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/logging/Logger.h"
#include "../../../../saccubus/meta/Thread.h"
#include "../../../../saccubus/meta/PlayInfo.h"
#include "../../../../saccubus/context/Thread.h"
#include "../../../../saccubus/python/PyBridge.h"
#include <sstream>
using namespace saccubus;

namespace saccubus{
namespace test {
namespace context{

class Context_ThreadTest : public ::testing::Test{
protected:
	python::PyBridge* bridge;
	meta::Thread* th;
	meta::PlayInfo* playInfo;
public:
	void SetUp(){
		bridge = new python::PyBridge(log_err);
		th = new meta::Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
		playInfo = new meta::PlayInfo(log_err, MATERIAL_DIR"getflv.txt");
	}
	void TearDown(){
		delete bridge;
		delete playInfo;
		delete th;
	}
};
TEST_F(Context_ThreadTest, LevelTest)
{
	saccubus::context::Thread* ctx = new saccubus::context::Thread(bridge, th, playInfo);

	ASSERT_EQ(1020U, ctx->commentSize());

	delete ctx;
}

}}}
