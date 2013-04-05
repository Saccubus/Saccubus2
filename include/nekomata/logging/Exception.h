/**
 * Nekomata
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
#include <exception>
#include <string>
#include <cstdarg>
#include <cinamo/Exception.h>

namespace nekomata {
namespace logging{

class Exception: public cinamo::Exception {
public:
	template <typename... Args>
	Exception(const char* fname, size_t line, const std::string& msg, Args... args) throw()
	:cinamo::Exception(fname, line, msg, args...){};
};

}}
