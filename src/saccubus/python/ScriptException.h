/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include "../logging/Exception.h"
#include <cstdarg>

namespace saccubus {
namespace python {

class ScriptException: public saccubus::logging::Exception {
public:
	template <typename... Args>
	ScriptException(const char* file, const size_t line, const std::string& fmt, Args... args):saccubus::logging::Exception(file,line,fmt,args...){}
	virtual ~ScriptException() throw();
};

}}
