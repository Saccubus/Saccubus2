/*
 * Exception.h
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

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
#endif /* EXCEPTION_H_ */
