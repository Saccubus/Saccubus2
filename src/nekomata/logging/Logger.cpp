/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
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

void Logger::e(std::string const& tag, const tree::Location* loc, std::string const& str, ...)
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
void Logger::w(std::string const& tag, const tree::Location* loc, std::string const& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::WARN_, tag, loc, str, list);
	va_end(list);
}
void Logger::i(std::string const& tag, const tree::Location* loc, std::string const& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::INFO_, tag, loc, str, list);
	va_end(list);
}
void Logger::d(std::string const& tag, const tree::Location* loc, std::string const& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::DEBUG_, tag, loc, str, list);
	va_end(list);
}
void Logger::v(std::string const& tag, const tree::Location* loc, std::string const& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::VERBOSE_, tag, loc, str, list);
	va_end(list);
}
void Logger::t(std::string const& tag, const tree::Location* loc, std::string const& str, ...)
{
	va_list list;
	va_start(list, str);
	msg(cinamo::Logger::TRACE_, tag, loc, str, list);
	va_end(list);
}

void Logger::msg(enum cinamo::Logger::Level level, std::string const& tag, const tree::Location* loc, std::string const& str, va_list list)
{
	std::stringstream ss;
	if(loc){
		ss << "[" << std::setw(3) <<  loc->getLineNo() << "," << std::setw(3) << loc->getColNo() << "]";
	}

	ss << " " << str;
	spirit_.msg(level, tag, ss.str(), list);
}

}}
