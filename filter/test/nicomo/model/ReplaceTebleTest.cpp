/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include <nicomo/model/ReplaceTable.h>

namespace nicomo {
namespace model {

TEST(ReplaceTableTest, SimpleTest)
{
	ReplaceTable table("a=b");
	ASSERT_EQ("bbbb", table.replace("abab"));
	ASSERT_EQ("cbcb", table.replace("cbcb"));
	ASSERT_EQ("cbbb", table.replace("cbab"));

	ReplaceTable tableWhole("%2Aa=b");
	ASSERT_EQ("b", tableWhole.replace("abab"));
	ASSERT_EQ("cbcb", tableWhole.replace("cbcb"));
	ASSERT_EQ("b", tableWhole.replace("cbab"));
}

TEST(ReplaceTableTest, ComplicatedTest)
{
	ReplaceTable table("aa=bc");
	ASSERT_EQ("abbc", table.replace("abaa"));
	ASSERT_EQ("abab", table.replace("abab"));

	ReplaceTable tableWhole("%2Aaa=bc");
	ASSERT_EQ("abab", tableWhole.replace("abab"));
	ASSERT_EQ("cbcb", tableWhole.replace("cbcb"));
	ASSERT_EQ("bc", tableWhole.replace("baab"));
}

TEST(ReplaceTableTest, MoreComplicatedTest)
{
	ReplaceTable table("b=c&a=b");
	ASSERT_EQ("cccc", table.replace("abab"));
	ASSERT_EQ("cccc", table.replace("acac"));
	ASSERT_EQ("cccc", table.replace("cbcb"));
	ASSERT_EQ("cccd", table.replace("abcd"));

	ReplaceTable tableWhole("%2Ab=c&a=b");
	ASSERT_EQ("c", tableWhole.replace("abab"));
	ASSERT_EQ("c", tableWhole.replace("acac"));
	ASSERT_EQ("c", tableWhole.replace("cbcb"));
	ASSERT_EQ("c", tableWhole.replace("abcd"));
	ASSERT_EQ("cdcd", tableWhole.replace("cdcd"));
}

}}
