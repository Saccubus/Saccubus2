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
#include <auto_ptr.h>
#include "../../TestCommon.h"
#include "../../../../saccubus/python/PyBridge.h"
#include "../../../../saccubus/meta/Thread.h"
#include "../../../../saccubus/meta/Video.h"
using namespace saccubus::python;
using namespace saccubus::meta;

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
	std::vector<std::pair<std::string, std::string> > args;
	args.push_back(std::pair<std::string, std::string>("resource-path", MATERIAL_DIR));
	std::auto_ptr<const Video> result(bridge.resolveResource("sm14097905", args));
	ASSERT_EQ(MATERIAL_DIR"sm14097905_video_test.mp4", result->videofile());
	ASSERT_EQ(1U, result->threadSize());
	ASSERT_EQ(1302222473LLU, result->threadBegin()->second->thread());
	ASSERT_EQ(1302222473LLU, result->threadBegin()->first);
}

TEST(PyBridgeTest, BasicFilterTest)
{
	PyBridge bridge(log_trace);
	Thread* th = new Thread(log_err, MATERIAL_DIR"sm14097905_thread_1302222473.xml");
	const Comment* com = *th->begin();
	ASSERT_EQ(true, bridge.askCommentShouldBeIgnored(MATERIAL_DIR"test_filter.py", *com));
}

}}}
