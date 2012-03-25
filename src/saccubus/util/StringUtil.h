/*
 * StringUtil.h
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#include <cstdarg>
#include <string>

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

namespace saccubus {
namespace util {

std::string format(const std::string& fmt, ...);
std::string formatv(const std::string& fmt, va_list args);
std::string decodePercent(const std::string& str);

}}
#endif /* STRINGUTIL_H_ */
