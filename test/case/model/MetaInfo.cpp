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
#include "../../../src/saccubus/model/MetaInfo.h"
using namespace saccubus::model;

namespace saccubus{
namespace test {
namespace model {

TEST(MetaInfoTest, BasicReadingTest)
{
	MetaInfo info(log_err, MATERIAL_DIR"sm14097905_meta_info.xml");
	ASSERT_EQ("【NIVA】 みくみくにしてあげる♪ 【サンプル1】", info.title());
}

}}}
