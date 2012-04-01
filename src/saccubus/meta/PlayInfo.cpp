/*
 * PlayInfo.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "PlayInfo.h"
#include <fstream>
#include <string>
#include "../util/Bundle.h"
#include "ReplaceTable.h"

namespace saccubus {
namespace meta {

PlayInfo::PlayInfo(logging::Logger& log, const std::string& filename)
:bundle(0)
,_replaceTable(0)
{
	std::ifstream stream(filename.c_str());
	std::string str;
	stream >> str;
	util::Bundle* b = new util::Bundle();
	b->readURLEncoded(str);
	this->bundle = b;

	user_id(bundle->getLong("user_id"));
	thread(bundle->getLong("thread_id"));
	is_premium(bundle->getBool("is_premium"));
	_replaceTable = bundle->has("ng_up") ? new ReplaceTable(bundle->getString("ng_up")) : 0;
}

PlayInfo::~PlayInfo() {
	delete bundle;
	if(_replaceTable){
		delete _replaceTable;
	}
}

const ReplaceTable* PlayInfo::replaceTable() const
{
	return _replaceTable;
}

}}
