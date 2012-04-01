/*
 * MetaInfo.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/meta/MetaInfo.h"
using namespace saccubus::meta;


TEST(MetaInfoTest, BasicReadingTest)
{
	MetaInfo info(log_err, MATERIAL_DIR"sm14097905_meta_info.xml");
	ASSERT_EQ("【NIVA】 みくみくにしてあげる♪ 【サンプル1】", info.title());
}

