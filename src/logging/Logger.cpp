/*
 * Logger.cpp
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#include "Logging.h"
#include <sstream>
#include <iomanip>
namespace logging{
Logger::Logger(std::ostream& stream, Level level)
:level(level), stream(stream)
{

}
Logger::~Logger()
{

}
void Logger::e(const std::string& tag, const std::string& str, const Location* loc)
{
	msg(ERROR, tag, str, loc);
}
void Logger::w(const std::string& tag, const std::string& str, const Location* loc)
{
	msg(WARNING, tag, str, loc);
}
void Logger::d(const std::string& tag, const std::string& str, const Location* loc)
{
	msg(DEBUG, tag, str, loc);
}
void Logger::v(const std::string& tag, const std::string& str, const Location* loc)
{
	msg(VERBOSE, tag, str, loc);
}
void Logger::t(const std::string& tag, const std::string& str, const Location* loc)
{
	msg(TRACE, tag, str, loc);
}

void Logger::msg(Level level, const std::string& tag, const std::string& str, const Location* loc)
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
	ss << str << std::endl;
	stream << ss.str();
}

}

