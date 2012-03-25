/*
 * VideoInfo.cpp
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#include <string>
#include "VideoInfo.h"

namespace saccubus {
namespace meta {

VideoInfo::VideoInfo(const std::string& info)
:bundle(util::Bundle::fromFormEncoded(info))
,replaceTable_(bundle.getString("ng_up"))
{
	user_id(bundle.getLong("user_id"));
	thread(bundle.getLong("thread_id"));
	is_premium(bundle.getBool("is_premium"));
}

VideoInfo::~VideoInfo() {
}

const ReplaceTable& VideoInfo::replaceTable() const
{
	return replaceTable_;
}


}}
