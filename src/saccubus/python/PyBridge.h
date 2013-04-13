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
#include <map>
#include <vector>
#include <nicomo/Model.h>
#include "../classdefs.h"

namespace saccubus {
namespace python {

class PyBridgeImpl;
class PyBridge {
private:
	cinamo::Logger& log;
	PyBridgeImpl* const impl;
public:
	PyBridge(cinamo::Logger& log);
	virtual ~PyBridge();
public:
	const nicomo::model::Video* resolveResource(const std::string& video_id, const std::multimap<std::string, std::string>& args);
	bool askCommentShouldBeIgnored(const std::string& filename, const nicomo::model::Comment& com);
};

}}
