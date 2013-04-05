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

#include "PlayInfo.h"
#include <fstream>
#include <string>
#include "../util/Bundle.h"
#include "ReplaceTable.h"

namespace saccubus {
namespace model {

PlayInfo::PlayInfo(cinamo::Logger& log, const std::string& filename)
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
	optional_thread(bundle->optLong("optional_thread_id", -1));
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
