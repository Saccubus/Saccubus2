/*
 * LoggingTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../saccubus/logging/Logger.h"
#include <sstream>

TEST(LoggerTest, LevelTest)
{
	std::ostringstream ss;
	Logger log1(ss, Logger::TRACE_);
	Logger log2(ss, Logger::VERBOSE_);
	Logger log3(ss, Logger::DEBUG_);
	Logger log4(ss, Logger::INFO_);
	Logger log5(ss, Logger::WARN_);
	Logger log6(ss, Logger::ERROR_);

	ASSERT_TRUE(log1.t());
	ASSERT_TRUE(log1.v());
	ASSERT_TRUE(log1.d());
	ASSERT_TRUE(log1.i());


	ASSERT_FALSE(log2.t());
	ASSERT_TRUE(log2.v());
	ASSERT_TRUE(log2.d());
	ASSERT_TRUE(log2.i());

	ASSERT_FALSE(log3.t());
	ASSERT_FALSE(log3.v());
	ASSERT_TRUE(log3.d());
	ASSERT_TRUE(log3.i());

	ASSERT_FALSE(log4.t());
	ASSERT_FALSE(log4.v());
	ASSERT_FALSE(log4.d());
	ASSERT_TRUE(log4.i());

	ASSERT_FALSE(log5.t());
	ASSERT_FALSE(log5.v());
	ASSERT_FALSE(log5.d());
	ASSERT_FALSE(log5.i());

	ASSERT_FALSE(log6.t());
	ASSERT_FALSE(log6.v());
	ASSERT_FALSE(log6.d());
	ASSERT_FALSE(log6.i());
}
TEST(LoggerTest, LogTest)
{
	std::ostringstream ss;
	Logger log(ss, Logger::DEBUG_);
	log.t("TestTag", "Test: %d", 12);
	ASSERT_EQ(0, ss.str().size());
	log.d("TestTag", "Test: %d", 12);
	ASSERT_GT(ss.str().size(), 0);
}

