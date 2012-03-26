/*
 * ReplaceItemTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/meta/ReplaceItem.h"
using namespace saccubus::meta;

TEST(ReplaceItemTest, SetGetTest)
{
	const ReplaceItem item("a", "b", true);
	ASSERT_EQ("a", item.from());
	ASSERT_EQ("b", item.to());
	ASSERT_TRUE(item.whole());
}


TEST(ReplaceItemTest, ReplaceTest)
{
	const ReplaceItem item("a", "b", false);
	ASSERT_EQ("bbbb", item.replace("abab"));
	ASSERT_EQ("cbcb", item.replace("cbcb"));

	const ReplaceItem itemWhole("a", "b", true);
	ASSERT_EQ("b", itemWhole.replace("abab"));
	ASSERT_EQ("bbbc", itemWhole.replace("bbbc"));
}


