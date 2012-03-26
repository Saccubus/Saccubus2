/*
 * StringUtilTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */
#include "../../TestCommon.h"
#include "../../../saccubus/util/StringUtil.h"
using namespace saccubus::util;

TEST(StringUtilTest, FormatTest)
{
	//うまいのがおもいうかばないぞー
	ASSERT_EQ("test 12 test", format("test %d test", 12));
	ASSERT_EQ("test test test", format("test %s test", "test"));
}

TEST(StringUtilTest, PercentDecodeTest)
{
	ASSERT_EQ("NOT_ENCODED", decodePercent("NOT_ENCODED"));
	ASSERT_EQ("test PERCENT_ENCOD\r\nED", decodePercent("test %50%45%52%43%45%4e%54%5f%45%4e%43%4f%44%0d%0a%45%44"));
}

TEST(StringUtilTest, StartsWithTest)
{
	ASSERT_TRUE(startsWith("abcdef",""));
	ASSERT_TRUE(startsWith("abcdef","abc"));
	ASSERT_FALSE(startsWith("abcdef","def"));
	ASSERT_TRUE(startsWith("abcdef","abcdef"));
}

TEST(StringUtilTest, EndsWithTest)
{
	ASSERT_FALSE(endsWith("abcdef","abc"));
	ASSERT_TRUE(endsWith("abcdef","def"));
	ASSERT_TRUE(endsWith("abcdef","abcdef"));
}

