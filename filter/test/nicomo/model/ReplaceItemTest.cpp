/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include <nicomo/model/ReplaceItem.h>
namespace nicomo {
namespace model {

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

}}
