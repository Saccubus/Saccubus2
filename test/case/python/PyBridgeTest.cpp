/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../../TestCommon.h"
#include "../../../src/saccubus/python/PyBridge.h"
#include "../../../src/saccubus/model/Thread.h"
#include "../../../src/saccubus/model/Video.h"
using namespace saccubus::python;
using namespace saccubus::model;

namespace saccubus{
namespace test {
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

}}}
