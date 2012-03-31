/*
 * ScriptException.cpp
 *
 *  Created on: 2012/03/31
 *      Author: psi
 */

#include "ScriptException.h"

namespace saccubus {
namespace python {

ScriptException::ScriptException(const std::string& fmt, ...)
:Exception()
{
	va_list lst;
	va_start(lst, fmt);
	init(fmt, lst);
	va_end(lst);
}

ScriptException::~ScriptException() throw(){
}

}}
