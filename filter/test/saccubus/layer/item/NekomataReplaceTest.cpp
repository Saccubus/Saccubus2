/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../../TestCommon.h"
#include <nekomata/system/System.h>
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../nicomo/model/Comment.h"
#include "../../../mock/MockSystem.h"
using nekomata::system::Replace;
using saccubus::layer::item::Comment;

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class NekomataReplaceOperationTest : public ::testing::Test
{
protected:
	samock::MockSystem mockSystem;
	Replace* replace;
	Comment* com;
public:
	void SetUp(){
		replace = new Replace(mockSystem);
		mockSystem.regist(replace);
	}
	void TearDown(){
		mockSystem.unregist(replace);
	}
};


TEST_F(NekomataReplaceOperationTest, BasicTest)
{
	replace->load("", "", true, "", true, true, 1, "", "");
	nicomock::model::Comment orig;
	orig.message("unchanged");
	saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
	com.onDeploy(&mockSystem);
	ASSERT_EQ(1U, com.color());
	ASSERT_EQ("unchanged", com.message());
}

TEST_F(NekomataReplaceOperationTest, SrcTest)
{
	replace->load("a", "b", true, "", true, true, 1, "", "");
	{
		nicomock::model::Comment orig;
		orig.message("a");
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
		com.onDeploy(&mockSystem);
		ASSERT_EQ("b", com.message());
	}

	{
		nicomock::model::Comment orig;
		orig.message("aaa");
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
		com.onDeploy(&mockSystem);
		ASSERT_EQ("b", com.message());
	}

	replace->load("a", "", true, "", false, true, 1, "", "");
	{
		nicomock::model::Comment orig;
		orig.message("aaa");
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
		com.onDeploy(&mockSystem);
		ASSERT_EQ("aaa", com.message());
		ASSERT_EQ(1U, com.color());
	}
	replace->load("a", "b", true, "", true, false, 1, "", "");
	{
		nicomock::model::Comment orig;
		orig.message("aaa");
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
		com.onDeploy(&mockSystem);
		ASSERT_EQ("aaa", com.message());
		ASSERT_EQ(1U, com.color());
	}

}

}}}}
