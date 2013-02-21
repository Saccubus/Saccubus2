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
#pragma once
#include <string>
#include "../util/ClassAccessor.h"
#include "../classdefs.h"

namespace saccubus {
namespace model {

/**
 * getflv内で指定される、
 * 動画の情報を表現するクラス
 * ！！　イミュータブル　！！
 */
class PlayInfo {
private:
	const util::Bundle* bundle;
	const ReplaceTable* _replaceTable;
	DEF_ATTR_ACCESSOR(public, private, long long, user_id);
	DEF_ATTR_ACCESSOR(public, private, bool, is_premium);
	DEF_ATTR_ACCESSOR(public, private, long long, thread);
	DEF_ATTR_ACCESSOR(public, private, long long, optional_thread);
public:
	PlayInfo(logging::Logger& log, const std::string& filename);
	virtual ~PlayInfo();
public:
	const ReplaceTable* replaceTable() const;
};

}}
