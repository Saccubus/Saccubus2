/*
 * StringUtilTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */
#include "../../TestCommon.h"
#include "../../../../saccubus/util/StringUtil.h"
using namespace saccubus::util;

TEST(StringUtilTest, FormatTest)
{
	ASSERT_EQ("NOT_FORMATTED", format("NOT_FORMATTED"));
	ASSERT_EQ("test %%% test", format("test %%%%%% test"));
	ASSERT_EQ("test 12 test", format("test %d test", 12));
	ASSERT_STRCASEEQ("test c test", format("test %x test", 0xc).c_str());
	ASSERT_STRCASEEQ("test 123 test", format("test %o test", 0123).c_str());
	ASSERT_STRCASEEQ("test \t test", format("test %c test", '\t').c_str());
	ASSERT_STRCASEEQ("test \r test", format("test %c test", 0x0d).c_str());
	ASSERT_STRCASEEQ("test \n test", format("test %c test", 0x0a).c_str());
	ASSERT_EQ("test test test", format("test %s test", "test"));
	ASSERT_EQ("test  test", format("test %s test", ""));
}

TEST(StringUtilTest, PercentDecodeTest)
{
	ASSERT_EQ("NOT_ENCODED", decodePercent("NOT_ENCODED"));
	ASSERT_EQ("test PERCENT_ENCOD\r\nED", decodePercent("test %50%45%52%43%45%4e%54%5f%45%4e%43%4f%44%0d%0a%45%44"));
}

TEST(StringUtilTest, StartsWithTest)
{
	ASSERT_TRUE(startsWith("abcdef","")); //この挙動はJavaと同じ
	ASSERT_TRUE(startsWith("abcdef","abc"));
	ASSERT_FALSE(startsWith("abcdef","def"));
	ASSERT_TRUE(startsWith("abcdef","abcdef"));
}

TEST(StringUtilTest, EndsWithTest)
{
	ASSERT_TRUE(endsWith("abcdef","")); //この挙動はJavaと同じ
	ASSERT_FALSE(endsWith("abcdef","abc"));
	ASSERT_TRUE(endsWith("abcdef","def"));
	ASSERT_TRUE(endsWith("abcdef","abcdef"));
}

