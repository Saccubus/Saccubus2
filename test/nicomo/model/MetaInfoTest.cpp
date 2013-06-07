/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../TestCommon.h"
#include <nicomo/model/MetaInfo.h>

namespace nicomo {
namespace model {

TEST(MetaInfoTest, BasicReadingTest)
{
	MetaInfo info(log_err, MATERIAL_DIR"sm14097905_meta_info.xml");
	ASSERT_EQ("【NIVA】 みくみくにしてあげる♪ 【サンプル1】", info.title());
}

}}
