/*
 * VideobundleTest.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include "../../TestCommon.h"
#include <fstream>
#include <istream>
#include <string>
#include "../../../../saccubus/util/Bundle.h"
using namespace saccubus::util;

static const std::string RPU_JSON="{\"count\":1595356,\"users\":[\"\\u3061\\u3073\\u7f8e\\u3002\",\"\\u308c\\u3093\\u3075\\u3041\",\"harutti92\",\"247 \\/ \\u4ec1\\u79d1\",\"nikola\",\"\\u4e9c\\u9f8d\",\"rc42\",\"\\u307e\\u3042\",\"\\u3081\\u3081\",\"shojikatyou\",\"\\u5929\\u6d25\\u7518\\u6817\",\"\\u30a2\\u30e9\\u30b8\\u30f3\\u30ca\\u30a4\\u30c8\",\"\\u3082\\u3081\\u3093\",\"sleep714\",\"\\u30e9\\u30de\",\"\\u3082\\u3063\\u3061\\u3083\\u3093\",\"\\u30ca\\u30eb\\u30b9\",\"Ryousuke\",\"ikaros\",\"\\u306f\\u308b\\u3054\\u3093\\u592a\\u90ce\"],\"extra\":18}";

TEST(VideobundleTest, ParseTest)
{
	std::ifstream stream(MATERIAL_DIR"getflv.txt");
	std::string str;
	stream >> str;
	Bundle bundle;
	bundle.readURLEncoded(str);
	ASSERT_FALSE(bundle.has(""));
	ASSERT_FALSE(bundle.has("__not_having_this__"));
	ASSERT_TRUE(bundle.has("thread_id"));
	ASSERT_EQ(1302222473, bundle.getLong("thread_id"));
	ASSERT_EQ(99, bundle.getLong("l"));
	ASSERT_EQ("http://smile-psu61.nicovideo.jp/smile?m=14097905.36147", bundle.getString("url"));
	ASSERT_EQ("http://www.smilevideo.jp/view/14097905/185957", bundle.getString("link"));
	ASSERT_EQ("http://msg.nicovideo.jp/36/api/", bundle.getString("ms"));
	ASSERT_EQ(185957, bundle.getLong("user_id"));
	ASSERT_TRUE(bundle.getBool("is_premium"));
	ASSERT_EQ("ψ（プサイ）", bundle.getString("nickname"));
	ASSERT_EQ(1332645296599, bundle.getLong("time"));
	ASSERT_TRUE(bundle.getBool("done"));
	ASSERT_EQ(1302222649, bundle.getLong("nicos_id"));
	ASSERT_EQ(70, bundle.getLong("ng_rv"));
	ASSERT_EQ("hiroba09.nicovideo.jp", bundle.getString("hms"));
	ASSERT_EQ(2529, bundle.getLong("hmsp"));
	ASSERT_EQ(1000000165, bundle.getLong("hmst"));
	ASSERT_EQ("1332645356.6-xTp4qlgXu2GtTIMPEb4w4ShIw", bundle.getString("hmstk"));
	ASSERT_EQ(RPU_JSON, bundle.getString("rpu"));
}

