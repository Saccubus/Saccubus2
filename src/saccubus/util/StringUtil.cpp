/*
 * StringUtil.cpp
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <stdio.h>
#include <auto_ptr.h>
#include <cstring>
#include <cstdlib>
#include "../logging/Exception.h"
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

std::string decodePercent(const std::string& str)
{
	char* from(new char[str.length()+1]);
	char* to(new char[str.length()+1]);
	std::memcpy(from, str.c_str(), str.length());
	from[str.length()] = '\0';
	size_t i=0,j=0;
	for(;i<str.length();++i, ++j){
		if(from[i] == '%'){
			char code[3];
			code[0] = from[i+1];
			code[1] = from[i+2];
			code[2] = '\0';
			i+=2;
			char* failed = 0;
			to[j] = static_cast<char>(std::strtol(code, &failed, 16) & 0xff);
			if(failed != &code[2]){
				throw logging::Exception("Failed to decode percent: %s", str.c_str());
			}
		}else if(from[i]=='+'){
			to[j] = ' ';
		}else{
			to[j] = from[i];
		}
	}
	to[j]='\0';

	return std::string(to);
}

}}
