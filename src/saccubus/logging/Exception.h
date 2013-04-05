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
#include <exception>
#include <string>
#include <cstdarg>
#include <cinamo/Exception.h>

namespace saccubus {
namespace logging {

/**
 * さきゅばすは基本的にこの例外を投げる
 */
class Exception : public cinamo::Exception {
public:
	Exception(const char* file, const size_t line) throw():cinamo::Exception(file, line){};
	template <typename... Args>
	Exception(const char* file, const size_t line, const std::string& fmt, Args... args):cinamo::Exception(file, line, fmt, args...){};
	Exception(const char* file, const size_t line, const std::string& fmt, va_list lst) throw():cinamo::Exception(file, line, fmt, lst){};
};

}}
