/*
 * StringUtil.cpp
 *
 *  Created on: 2012/02/26
 *      Author: psi
 */

#include "StringUtil.h"
#include <cstdio>
#include <cstdarg>

namespace nekomata {
namespace utl {

std::string format(const std::string& msg, ...)
{
	va_list list;
	va_start(list, msg);
	std::string str(nekomata::utl::format(msg, list));
	va_end(list);
	return str;
}
std::string format(const std::string& msg, va_list arg)
{
	char buff[1024];
	const size_t len = vsnprintf(buff, 1024, msg.c_str(), arg);
	if(len > 0){
		return std::string(buff);
	}else{
		return "Too long";
	}
}

}
}
