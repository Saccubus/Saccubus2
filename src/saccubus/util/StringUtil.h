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
/* FIXME: 明らかに猫又側と被ってる。
 * 共有ライブラリとしてくくりだしたいけど、
 * 猫又の独立性を高めたい、というのもある。 */

namespace saccubus {
namespace util {

std::string format(const std::string& fmt, ...);
std::string formatv(const std::string& fmt, va_list args);
std::string decodePercent(const std::string& str);
bool startsWith(const std::string& target, const std::string& prefix);
bool endsWith(const std::string& target, const std::string& suffix);

}}
#endif /* STRINGUTIL_H_ */
