/*
 * ScriptException.h
 *
 *  Created on: 2012/03/31
 *      Author: psi
 */

#ifndef SCRIPTEXCEPTION_H_
#define SCRIPTEXCEPTION_H_

#include "../logging/Exception.h"
#include <cstdarg>

namespace saccubus {
namespace python {

class ScriptException: public saccubus::logging::Exception {
public:
	ScriptException(const std::string& fmt, ...);
	virtual ~ScriptException() throw();
};

}}
#endif /* SCRIPTEXCEPTION_H_ */
