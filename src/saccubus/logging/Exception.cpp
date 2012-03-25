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

Exception::Exception(const std::string& fmt, ...) throw()
{
	try{
		va_list lst;
		va_start(lst, fmt);
		this->msg = util::formatv(fmt, lst);
		va_end(lst);
	}catch(...){
		msg = "[BUG] Failed to format string!!";
	}
}

Exception::~Exception() throw(){
}

std::string Exception::what()
{
	return msg;
}

}}
