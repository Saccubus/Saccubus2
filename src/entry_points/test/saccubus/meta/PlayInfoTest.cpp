/*
 * PlayInfoTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/meta/PlayInfo.h"
#include "../../../../saccubus/meta/ReplaceTable.h"
using namespace saccubus::meta;

TEST(PlayInfoTest, InfoTest)
{
	PlayInfo info(MATERIAL_DIR"getflv.txt");
	ASSERT_TRUE(info.is_premium());
	ASSERT_EQ(1302222473, info.thread());
	ASSERT_EQ(185957, info.user_id());
}

TEST(PlayInfoTest, ReplaceTest)
{
	PlayInfo info(MATERIAL_DIR"getflv.txt");
	const ReplaceTable* table = info.replaceTable();
	ASSERT_EQ("tt", table->replace("test"));
	ASSERT_EQ("att", table->replace("atest"));
	ASSERT_EQ("tt", table->replace("atest2"));
	ASSERT_EQ("tt", table->replace("test2test2"));
}

