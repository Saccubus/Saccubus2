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
#include <cinamo/Logger.h>
#include <tinyxml2.h>
#include "ReplaceTable.h"

namespace nicomo {
namespace model {

class MetaInfo final{
	DEFINE_MEMBER(public, private, std::string, title);
public:
	MetaInfo(cinamo::Logger& log, tinyxml2::XMLElement* elm);
	MetaInfo(cinamo::Logger& log, tinyxml2::XMLDocument* doc);
	MetaInfo(cinamo::Logger& log, const std::string& filename);
	~MetaInfo() = default;
private:
	void read(cinamo::Logger& log, tinyxml2::XMLElement* elm);
};

}}
