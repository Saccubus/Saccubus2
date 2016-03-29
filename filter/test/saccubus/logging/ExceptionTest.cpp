/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include "../../../src/saccubus/logging/Exception.h"
using namespace saccubus::logging;

namespace saccubus{
namespace test {
namespace logging{

TEST(ExceptionTest, ThrowingTest)
{
	ASSERT_THROW(throw Exception(__FILE__, __LINE__, "Hey!"), Exception);
}

TEST(ExceptionTest, MessageTest)
{
	Exception e(__FILE__, __LINE__, "Hey!");
	ASSERT_EQ("Hey!", e.msg());

	Exception e2(__FILE__, __LINE__, "%d", 12);
	ASSERT_EQ("12", e2.msg());
}

}}}

