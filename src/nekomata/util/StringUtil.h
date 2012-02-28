/*
 * StringUtil.h
 *
 *  Created on: 2012/02/26
 *      Author: psi
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <cstdarg>

namespace nekomata {
namespace utl {

std::string format(const std::string& msg, ...);
std::string format(const std::string& msg, va_list arg);

}}
#endif /* STRINGUTIL_H_ */
