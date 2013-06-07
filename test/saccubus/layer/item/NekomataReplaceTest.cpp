/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#if 0

#include "../../../TestCommon.h"
#include <nekomata/system/System.h>
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../../src/saccubus/layer/item/CommentPipeLine.h"
#include "../../../mock/model/Comment.h"
#include "../../../mock/MockSystem.h"
using namespace saccubus::mock;
using nekomata::system::Replace;
using saccubus::layer::item::NekomataReplaceOperation;
using saccubus::layer::item::Comment;

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class NekomataReplaceOperationTest : public ::testing::Test
{
protected:
	mock::MockSystem mockSystem;
	Replace* replace;
	Comment* com;
public:
	void SetUp(){
		replace = new Replace(mockSystem);
		com = new Comment(0, 0);
	}
	void TearDown(){
		delete com;
		delete replace;
	}
};


TEST_F(NekomataReplaceOperationTest, BasicTest)
{
	replace->load("", "", true, "", true, true, 1, "", "");
	com->message("unchanged");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ(1U, com->color());
	ASSERT_EQ("unchanged", com->message());
}

TEST_F(NekomataReplaceOperationTest, SrcTest)
{
	replace->load("a", "b", true, "", true, true, 1, "", "");
	com->message("a");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("b", com->message());

	com->message("aaa");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("aaa", com->message());

	replace->load("a", "", true, "", false, true, 1, "", "");
	com->message("aaa");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("aaa", com->message());
	ASSERT_EQ(1U, com->color());

	replace->load("a", "b", true, "", true, false, 1, "", "");
	com->message("aaa");
	NekomataReplaceOperation::apply(replace, com);
	ASSERT_EQ("b", com->message());
	ASSERT_EQ(1U, com->color());
}

}}}}

#endif
