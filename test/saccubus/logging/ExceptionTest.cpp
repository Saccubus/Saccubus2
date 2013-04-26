/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
