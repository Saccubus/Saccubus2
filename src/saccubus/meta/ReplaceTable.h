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

#ifndef REPLACETABLE_H_
#define REPLACETABLE_H_

#include <vector>
#include <string>
#include "./ReplaceItem.h"

namespace saccubus {
namespace meta {
/**
 * getflv内で指定される、
 * コメントフィルタ機能の置換テーブル全体を表現
 * ！！　イミュータブル　！！
 */
class ReplaceTable {
private:
	std::vector<const ReplaceItem*> replaceList;
public:
	ReplaceTable(const std::string& entry);
	virtual ~ReplaceTable();
public:
	std::string replace(const std::string& target) const;
};

}}
#endif /* REPLACETABLE_H_ */
