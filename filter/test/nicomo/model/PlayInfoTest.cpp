/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include <nicomo/model/PlayInfo.h>
#include <nicomo/model/ReplaceTable.h>

namespace nicomo {
namespace model {

TEST(PlayInfoTest, BasicReadingTest)
{
	PlayInfo info(log_err, MATERIAL_DIR"getflv.txt");
	ASSERT_TRUE(info.is_premium());
	ASSERT_EQ(1302222473, info.thread());
	ASSERT_EQ(185957, info.user_id());
	ASSERT_LE(info.optional_thread(), 0);
}

TEST(PlayInfoTest, ReplaceTest)
{
	PlayInfo info(log_err, MATERIAL_DIR"getflv.txt");
	const ReplaceTable* table = info.replaceTable();
	ASSERT_EQ("tt", table->replace("test"));
	ASSERT_EQ("att", table->replace("atest"));
	ASSERT_EQ("tt", table->replace("atest2"));
	ASSERT_EQ("tt", table->replace("test2test2"));
}

}}
