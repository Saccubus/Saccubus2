/*
 * PyBridgeTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */
#include <string>
#include <map>
#include <vector>
#include "../../TestCommon.h"
#include "../../../../saccubus/python/PyBridge.h"
using namespace saccubus::python;

TEST(PyBridgeTest, InitTest)
{
	PyBridge bridge(log_trace);
}

TEST(PyBridgeTest, BasicResolveTest)
{
	PyBridge bridge(log_trace);
	std::vector<std::pair<std::string, std::string> > args;
	args.push_back(std::pair<std::string, std::string>("resource-path", MATERIAL_DIR));
	std::map<std::string, std::string> result = bridge.resolveResource("sm14097905", args);
	ASSERT_EQ(MATERIAL_DIR"sm14097905_video_test.mp4", result["video"]);
}

