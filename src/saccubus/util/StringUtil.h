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
std::string format(const std::string& fmt, std::va_list args);

}}
#endif /* STRINGUTIL_H_ */
