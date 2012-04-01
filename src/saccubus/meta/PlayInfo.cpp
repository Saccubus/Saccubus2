/*
 * PlayInfo.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "PlayInfo.h"

namespace saccubus {
namespace meta {

PlayInfo::PlayInfo(const std::string& info)
:bundle(util::Bundle::fromFormEncoded(info))
,_replaceTable(bundle.getString("ng_up"))
{
	user_id(bundle.getLong("user_id"));
	thread(bundle.getLong("thread_id"));
	is_premium(bundle.getBool("is_premium"));
}

PlayInfo::~PlayInfo() {
}

const ReplaceTable& PlayInfo::replaceTable() const
{
	return _replaceTable;
}

}}
