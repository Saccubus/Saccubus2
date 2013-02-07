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

#include "Dumpable.h"
#include "../util/StringUtil.h"
#include "../tree/Location.h"

namespace nekomata{
namespace logging{
Logger::Logger(std::ostream& stream, enum Level level)
:level(level), stream(stream)
{

}
Logger::~Logger()
{

}

void Logger::e(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(ERROR_, tag, loc, str, list);
	va_end(list);
}

void Logger::e(Exception& exception)
{
	msg(ERROR_, "Exception", 0, exception.what(), 0);
}
void Logger::w(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(WARNING_, tag, loc, str, list);
	va_end(list);
}
void Logger::i(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(INFO_, tag, loc, str, list);
	va_end(list);
}
void Logger::d(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(DEBUG_, tag, loc, str, list);
	va_end(list);
}
void Logger::v(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(VERBOSE_, tag, loc, str, list);
	va_end(list);
}
void Logger::t(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(TRACE_, tag, loc, str, list);
	va_end(list);
}

void Logger::msg(enum Level level, const std::string& tag, const tree::Location* loc, const std::string& str, va_list list)
{
	if(level < this->level){
		return;
	}
	std::stringstream ss;
	switch(level){
	case TRACE_:
		ss << "[T]";
		break;
	case VERBOSE_:
		ss << "[V]";
		break;
	case DEBUG_:
		ss << "[D]";
		break;
	case INFO_:
		ss << "[I]";
		break;
	case WARNING_:
		ss << "[W]";
		break;
	case ERROR_:
		ss << "[E]";
		break;
	}
	ss << "[" << std::setw(10) << tag << "]";
	if(loc){
		ss << "[" << std::setw(3) <<  loc->getLineNo() << "," << std::setw(3) << loc->getColNo() << "]";
	}

	ss << " " << util::formatv(str.c_str(), list);
	stream << ss.str() << std::endl;
	stream.flush();
}

}}
