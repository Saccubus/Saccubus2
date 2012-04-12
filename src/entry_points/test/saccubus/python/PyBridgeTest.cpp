/*
 * PyBridgeTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */
#include <string>
#include <map>
#include <vector>
#include <auto_ptr.h>
#include "../../TestCommon.h"
#include "../../../../saccubus/python/PyBridge.h"
#include "../../../../saccubus/meta/Thread.h"
#include "../../../../saccubus/meta/Video.h"
using namespace saccubus::python;
using namespace saccubus::meta;

TEST(PyBridgeTest, InitTest)
{
	PyBridge bridge(log_err);
}

TEST(PyBridgeTest, BasicResolveTest)
{
	PyBridge bridge(log_err);
	std::vector<std::pair<std::string, std::string> > args;
	args.push_back(std::pair<std::string, std::string>("resource-path", MATERIAL_DIR));
	std::auto_ptr<const Video> result(bridge.resolveResource("sm14097905", args));
	ASSERT_EQ(MATERIAL_DIR"sm14097905_video_test.mp4", result->videofile());
	ASSERT_EQ(1, result->threadSize());
	ASSERT_EQ(1302222473L, result->threadBegin()->second->thread());
	ASSERT_EQ(1302222473L, result->threadBegin()->first);
}

TEST(PyBridgeTest, BasicFilterTest)
{
	PyBridge bridge(log_trace);
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	const Comment* com = *th->begin();
	ASSERT_EQ(true, bridge.askCommentShouldBeIgnored(MATERIAL_DIR"test_filter.py", *com));
}

