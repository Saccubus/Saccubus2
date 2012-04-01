/*
 * ExceptionTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/logging/Exception.h"
using namespace saccubus::logging;

TEST(ExceptionTest, ThrowingTest)
{
	ASSERT_THROW(throw Exception("Hey!"), Exception);
}

TEST(ExceptionTest, MessageTest)
{
	Exception e("Hey!");
	ASSERT_EQ("Hey!", e.what());

	Exception e2("%d", 12);
	ASSERT_EQ("12", e2.what());
}


