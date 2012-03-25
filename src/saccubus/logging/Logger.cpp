/*
 * Logger.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Logger.h"
#include "Exception.h"
#include "../util/StringUtil.h"

namespace saccubus {
namespace logging{

Logger::Logger(std::ostream& stream, enum Level level)
:stream(stream), level(level)
{
}

void Logger::msg(enum Level level, const std::string& tag, const std::string& fmt, std::va_list args)
{
	std::stringstream ss;
	if(level < this->level){
		return;
	}
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
	case WARN_:
		ss << "[W]";
		break;
	case ERROR_:
		ss << "[E]";
		break;
	default:
		throw Exception("[BUG][FIXME] Invalid log level!!");
	}
	ss << "[" << std::setw(16) << tag << "] ";
	ss << util::format(fmt, args) << std::endl;
	stream << ss.str();
	stream.flags();
}

Logger::~Logger() {
}

bool Logger::t()
{
	return this->level <= TRACE_;
}
void Logger::t(const std::string& tag, const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(TRACE_, tag, fmt, lst);
	va_end(lst);

}
bool Logger::v()
{
	return this->level <= VERBOSE_;
}

void Logger::v(const std::string& tag, const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(VERBOSE_, tag, fmt, lst);
	va_end(lst);
}
bool Logger::d()
{
	return this->level <= DEBUG_;
}
void Logger::d(const std::string& tag, const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(DEBUG_, tag, fmt, lst);
	va_end(lst);
}
bool Logger::i()
{
	return this->level <= INFO_;
}
void Logger::i(const std::string& tag, const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(INFO_, tag, fmt, lst);
	va_end(lst);
}
void Logger::w(const std::string& tag, const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(WARN_, tag, fmt, lst);
	va_end(lst);
}
void Logger::e(const std::string& tag, const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	msg(ERROR_, tag, fmt, lst);
	va_end(lst);
}

}}
