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
#include "../classdefs.h"
#include "../util/ClassAccessor.h"
#include "ReplaceTable.h"
#include <string>
#include <libxml2/libxml/tree.h>
#include <cinamo/Logger.h>

namespace saccubus {
namespace model {

class MetaInfo{
	DEF_ATTR_ACCESSOR(public, private, std::string, title);
public:
	MetaInfo(cinamo::Logger& log, xmlNode* node);
	MetaInfo(cinamo::Logger& log, xmlDoc* doc);
	MetaInfo(cinamo::Logger& log, const std::string& filename);
	virtual ~MetaInfo();
private:
	void read(cinamo::Logger& log, xmlNode* node);
};

}}
