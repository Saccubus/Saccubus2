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
#include <cinamo/ClassUtil.h>
#include "Comment.h"

namespace nicomo {
namespace model {

/**
 * XML内でのスレッドを表現するクラス
 * ！！　イミュータブル（変更不可）　！！
 */
class Thread {
	DEFINE_MEMBER(public, private, unsigned long long, thread)
	DEFINE_MEMBER(public, private, unsigned long long, ticket)
	DEFINE_MEMBER(public, private, unsigned long long, server_time)
	std::vector<const Comment*> chatList;
public:
	typedef std::vector<const Comment*>::const_iterator Iterator;
	Thread(cinamo::Logger& log, tinyxml2::XMLElement* node);
	Thread(cinamo::Logger& log, tinyxml2::XMLDocument* doc);
	Thread(cinamo::Logger& log, const std::string& filename);
	virtual ~Thread();
private:
	void read(cinamo::Logger& log, tinyxml2::XMLElement* elm);
public:
	Iterator begin() const;
	Iterator end() const;
	size_t size() const;
};

}}
