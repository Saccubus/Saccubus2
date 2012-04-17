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

#ifndef SACCUBUS_EXCEPTION_H_
#define SACCUBUS_EXCEPTION_H_

#include <exception>
#include <string>
#include <cstdarg>

namespace saccubus {
namespace logging {

/**
 * FIXME: 猫又と被ってる。括りだししたほうがいい？
 */

/**
 * さきゅばすは基本的にこの例外を投げる
 */
class Exception : public std::exception {
private:
	std::string msg;
protected:
	void init(const std::string& fmt, va_list lst) throw();
public:
	Exception() throw();
	Exception(const std::string& fmt, ...) throw();
	Exception(const std::string& fmt, va_list lst) throw();
	virtual ~Exception() throw();
	std::string what();
};

}}
#endif /* SACCUBUS_EXCEPTION_H_ */
