/*
 * Exception.cpp
 *
 *  Created on: 2012/02/23
 *      Author: psi
 */

#include "Exception.h"
#include "../util/StringUtil.h"
#include <sstream>

namespace nekomata{
namespace logging{

Exception::Exception(const std::string& fname, size_t line, const std::string& msg, ...) throw(){
	try {
		std::stringstream ss;
		ss << "(" << fname << ":" << line;
		va_list arg;
		va_start(arg, msg);
		ss << utl::format(msg, arg);
		this->msg = ss.str();
		va_end(arg);
	} catch (...) {
		this->msg= "Error occured while throw Exception!";
	}
}

Exception::~Exception() throw(){
}

}
}
