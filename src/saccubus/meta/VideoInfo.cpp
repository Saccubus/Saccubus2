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
}

VideoInfo::~VideoInfo() {
}

const ReplaceTable& VideoInfo::replaceTable() const
{
	return replaceTable_;
}


}}
