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

#include "StringUtil.h"
#include <cstdio>
#include <cstdarg>

namespace nekomata {
namespace util {

std::string format(const std::string& msg, ...)
{
	va_list list;
	va_start(list, msg);
	std::string str(util::formatv(msg, list));
	va_end(list);
	return str;
}
std::string formatv(const std::string& msg, va_list arg)
{
	char buff[1024];
	const size_t len = vsnprintf(buff, 1024, msg.c_str(), arg);
	if(len > 0){
		return std::string(buff);
	}else{
		return "Too long";
	}
}

}}
