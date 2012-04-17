/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdarg>
#include <string>

#ifndef SACCUBUS_STRINGUTIL_H_
#define SACCUBUS_STRINGUTIL_H_
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
#endif /* SACCUBUS_STRINGUTIL_H_ */
