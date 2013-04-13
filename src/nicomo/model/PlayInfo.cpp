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

#include <fstream>
#include <string>
#include <nicomo/model/PlayInfo.h>
#include <nicomo/model/ReplaceTable.h>

namespace nicomo {
namespace model {

PlayInfo::PlayInfo(cinamo::Logger& log, const std::string& filename)
:replaceTable_(nullptr)
{
	std::ifstream stream(filename.c_str());
	std::string str;
	stream >> str;
	cinamo::FormPayload b;
	b.readURLEncoded(str);

	user_id(b.getLong("user_id"));
	thread(b.getLong("thread_id"));
	is_premium(b.getBool("is_premium"));
	optional_thread(b.optLong("optional_thread_id", -1));
	replaceTable_ = b.has("ng_up") ? new ReplaceTable(b.getString("ng_up")) : 0;
}

PlayInfo::~PlayInfo() {
	if(replaceTable_){
		delete replaceTable_;
	}
}

const ReplaceTable* PlayInfo::replaceTable() const
{
	return replaceTable_;
}

}}
