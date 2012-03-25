/*
 * VideoInfoTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include <fstream>
#include "../../../saccubus/meta/VideoInfo.h"
using namespace saccubus::meta;

TEST(VideoInfoTest, InfoTest)
{
	std::ifstream stream(MATERIAL_DIR"getflv.txt");
	std::string str;
	stream >> str;
	VideoInfo info(str);
	ASSERT_TRUE(info.is_premium());
	ASSERT_EQ(1302222473, info.thread());
	ASSERT_EQ(185957, info.user_id());
}

TEST(VideoInfoTest, ReplaceTest)
{
	std::ifstream stream(MATERIAL_DIR"getflv.txt");
	std::string str;
	stream >> str;
	VideoInfo info(str);
	const ReplaceTable& table = info.replaceTable();
	ASSERT_EQ("tt", table.replace("test"));
	ASSERT_EQ("att", table.replace("atest"));
	ASSERT_EQ("tt", table.replace("atest2"));
	ASSERT_EQ("tt", table.replace("test2test2"));
}

