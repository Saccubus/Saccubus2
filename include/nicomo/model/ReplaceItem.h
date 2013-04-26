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
#include <cinamo/ClassUtil.h>

namespace nicomo {
namespace model {

/**
 * getflv内で指定される、
 * コメントフィルタ機能の置換テーブルの一つを表現
 * ！！　イミュータブル　！！
 */
class ReplaceItem final{
private:
	DEFINE_MEMBER_CONST(public, std::string, from);
	DEFINE_MEMBER_CONST(public, std::string, to);
	DEFINE_MEMBER_CONST(public, bool, whole);
public:
	ReplaceItem(const std::string& from, const std::string& to, bool whole);
	ReplaceItem(const ReplaceItem& other);
	~ReplaceItem() = default;
public:
	std::string replace(const std::string& target) const;
};

}}
