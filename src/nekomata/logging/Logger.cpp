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

#include <sstream>
#include <iomanip>
#include <cstdio>
#include <nekomata/logging/Exception.h>
#include <nekomata/logging/Logging.h>
#include <cinamo/String.h>

#include "Dumpable.h"
#include "../tree/Location.h"

namespace nekomata{
namespace logging{
Logger::Logger(cinamo::Logger& spirit)
:spirit_(spirit)
{

}
Logger::~Logger()
{

}

void Logger::e(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::ERROR_, tag, loc, str, list);
	va_end(list);
}

void Logger::e(Exception& exception)
{
	msg(cinamo::Logger::ERROR_, "Exception", 0, exception.what(), 0);
}
void Logger::w(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::WARN_, tag, loc, str, list);
	va_end(list);
}
void Logger::i(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::INFO_, tag, loc, str, list);
	va_end(list);
}
void Logger::d(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::DEBUG_, tag, loc, str, list);
	va_end(list);
}
void Logger::v(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::VERBOSE_, tag, loc, str, list);
	va_end(list);
}
void Logger::t(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::TRACE_, tag, loc, str, list);
	va_end(list);
}

void Logger::msg(enum cinamo::Logger::Level level, const std::string& tag, const tree::Location* loc, const std::string& str, va_list list)
{
	std::stringstream ss;
	if(loc){
		ss << "[" << std::setw(3) <<  loc->getLineNo() << "," << std::setw(3) << loc->getColNo() << "]";
	}

	ss << " " << str;
	spirit_.msg(level, tag, ss.str(), list);
}

}}
