/*
 * Exception.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include "../util/StringUtil.h"
#include "Exception.h"

namespace saccubus {
namespace logging {

Exception::Exception() throw()
{
}

Exception::Exception(const std::string& fmt, ...) throw()
{
	va_list lst;
	va_start(lst, fmt);
	init(fmt, lst);
	va_end(lst);
}

Exception::Exception(const std::string& fmt, va_list lst) throw()
{
	init(fmt, lst);
}

void Exception::init(const std::string& fmt, va_list lst) throw()
{
	try{
		this->msg = util::formatv(fmt, lst);
	}catch(...){
		this->msg = "[BUG] Failed to format string!!";
	}
}

Exception::~Exception() throw(){
}

std::string Exception::what()
{
	return msg;
}

}}
