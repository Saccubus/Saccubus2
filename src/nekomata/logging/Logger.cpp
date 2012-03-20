/*
 * Logger.cpp
 *
 *  Created on: 2012/02/18
 *      Author: psi
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
	std::va_list list;
	va_start(list, str);
	msg(ERROR, tag, loc, str, list);
	va_end(list);
}

void Logger::e(Exception& exception)
{
	msg(ERROR, "Exception", 0, exception.what(), 0);
}
void Logger::w(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	std::va_list list;
	va_start(list, str);
	msg(WARNING, tag, loc, str, list);
	va_end(list);
}
void Logger::d(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	std::va_list list;
	va_start(list, str);
	msg(DEBUG, tag, loc, str, list);
	va_end(list);
}
void Logger::v(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	std::va_list list;
	va_start(list, str);
	msg(VERBOSE, tag, loc, str, list);
	va_end(list);
}
void Logger::t(const std::string& tag, const tree::Location* loc, const std::string& str, ...)
{
	std::va_list list;
	va_start(list, str);
	msg(TRACE, tag, loc, str, list);
	va_end(list);
}

void Logger::msg(enum Level level, const std::string& tag, const tree::Location* loc, const std::string& str, va_list list)
{
	if(level < this->level){
		return;
	}
	std::stringstream ss;
	switch(level){
	case TRACE:
		ss << "[T]";
		break;
	case VERBOSE:
		ss << "[V]";
		break;
	case DEBUG:
		ss << "[D]";
		break;
	case WARNING:
		ss << "[W]";
		break;
	case ERROR:
		ss << "[E]";
		break;
	}
	ss << "[" << std::setw(10) << tag << "]";
	if(loc){
		ss << "[" << std::setw(3) <<  loc->getLineNo() << "," << std::setw(3) << loc->getColNo() << "]";
	}

	ss << " " << util::format(str.c_str(), list);
	stream << ss.str() << std::endl;
	stream.flush();
}

}}
