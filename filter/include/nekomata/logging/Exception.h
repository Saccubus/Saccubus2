/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <exception>
#include <string>
#include <cstdarg>
#include <cinamo/Exception.h>

namespace nekomata {
namespace logging{

class Exception: public cinamo::Exception {
public:
	template <typename... Args>
	Exception(const char* fname, size_t line, const std::string& msg, Args... args) throw()
	:cinamo::Exception(fname, line, msg, args...){};
};

}}
