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
#include "../../TestCommon.h"
#include "../../../../saccubus/meta/Comment.h"

namespace saccubus {
namespace mock {
namespace meta {

class Comment: public saccubus::meta::Comment {
public:
	Comment();
	virtual ~Comment();
public:
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, thread);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, no);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, float, vpos);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, date);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, deleted);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, long long, score);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, std::string, user_id);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, std::string, mail);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, std::string, message);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, anonymity);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, leaf);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, premium);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, fork);
};

}}}
