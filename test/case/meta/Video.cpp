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

#include "../../TestCommon.h"
#include <fstream>
#include "../../../src/saccubus/meta/Video.h"
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
