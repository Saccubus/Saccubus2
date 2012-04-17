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
#include "../../../../saccubus/meta/PlayInfo.h"
#include "../../../../saccubus/meta/ReplaceTable.h"
using namespace saccubus::meta;

namespace saccubus{
namespace test {
namespace meta {

TEST(PlayInfoTest, BasicReadingTest)
{
	PlayInfo info(log_err, MATERIAL_DIR"getflv.txt");
	ASSERT_TRUE(info.is_premium());
	ASSERT_EQ(1302222473, info.thread());
	ASSERT_EQ(185957, info.user_id());
}

TEST(PlayInfoTest, ReplaceTest)
{
	PlayInfo info(log_err, MATERIAL_DIR"getflv.txt");
	const ReplaceTable* table = info.replaceTable();
	ASSERT_EQ("tt", table->replace("test"));
	ASSERT_EQ("att", table->replace("atest"));
	ASSERT_EQ("tt", table->replace("atest2"));
	ASSERT_EQ("tt", table->replace("test2test2"));
}

}}}
