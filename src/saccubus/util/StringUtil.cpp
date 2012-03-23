/*
 * StringUtil.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <stdio.h>
#include "StringUtil.h"

namespace saccubus {
namespace util {

std::string format(const std::string& fmt, ...)
{
	std::va_list lst;
	va_start(lst, fmt);
	std::string res(format(fmt, lst));
	va_end(lst);
	return res;
}
std::string format(const std::string& fmt, std::va_list args)
{
	char buff[8192];
	vsnprintf(buff, 8192, fmt.c_str(), args);
	return buff;
}

}}
