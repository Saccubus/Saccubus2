/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <nicomo/Model.h>
#include "../../TestCommon.h"
#include "../../../src/saccubus/python/PyBridge.h"
using namespace nicomo::model;

namespace saccubus{
namespace python {

TEST(PyBridgeTest, InitTest)
{
	PyBridge bridge(log_err);
}

TEST(PyBridgeTest, BasicResolveTest)
{
	PyBridge bridge(log_err);
	std::multimap<std::string, std::string> args;
	args.insert(std::pair<std::string, std::string>("resource-path", MATERIAL_DIR));
	args.insert(std::pair<std::string, std::string>("user", "saccubus@gmail.com"));
	args.insert(std::pair<std::string, std::string>("password", "test1234"));
	args.insert(std::pair<std::string, std::string>("cookie", "own"));
	std::auto_ptr<const Video> result(bridge.resolveResource("sm14097905", args));
	ASSERT_EQ(MATERIAL_DIR"sm14097905_video_test.mp4", result->videofile());
	ASSERT_EQ(1U, result->threadSize());
	std::map<unsigned long long, const Thread*>::value_type const& beg = *result->threadBegin();
	ASSERT_EQ(1302222473LLU, beg.second->thread());
	ASSERT_EQ(1302222473LLU, beg.first);
}

TEST(PyBridgeTest, BasicFilterTest)
{
	PyBridge bridge(log_trace);
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	const Comment* com = *th->begin();
	ASSERT_EQ(true, bridge.askCommentShouldBeIgnored(MATERIAL_DIR"test_filter.py", *com));
}

}}
