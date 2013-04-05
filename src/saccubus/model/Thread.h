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
#include <cinamo/Logger.h>
#include <libxml2/libxml/tree.h>
#include "Comment.h"
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace model {

/**
 * XML内でのスレッドを表現するクラス
 * ！！　イミュータブル（変更不可）　！！
 */
class Thread {
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, thread)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, ticket)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, server_time)
	std::vector<const Comment*> chatList;
public:
	typedef std::vector<const Comment*>::const_iterator Iterator;
	Thread(cinamo::Logger& log, xmlNode* node);
	Thread(cinamo::Logger& log, xmlDoc* doc);
	Thread(cinamo::Logger& log, const std::string& filename);
	virtual ~Thread();
private:
	void read(cinamo::Logger& log, xmlNode* node);
public:
	Iterator begin() const;
	Iterator end() const;
	size_t size() const;
};

}}
