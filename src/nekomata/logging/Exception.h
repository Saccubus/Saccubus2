/*
 * Exception.h
 *
 *  Created on: 2012/02/23
 *      Author: psi
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>
#include <cstdarg>

namespace nekomata {
namespace logging{

class Exception: public std::exception {
private:
	std::string msg;
	std::string fname;
	size_t line;
public:
	Exception(const std::string& fname, size_t line, const std::string& msg, ...) throw();
	virtual ~Exception() throw();
	virtual const std::string& what() throw(){return msg;};
};

}
}
#endif /* EXCEPTION_H_ */
