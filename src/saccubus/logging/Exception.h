/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <exception>
#include <string>
#include <cstdarg>
#include <cinamo/Exception.h>

namespace saccubus {
namespace logging {

/**
 * さきゅばすは基本的にこの例外を投げる
 */
class Exception : public cinamo::Exception {
public:
	Exception(const char* file, const size_t line) throw():cinamo::Exception(file, line){};
	template <typename... Args>
	Exception(const char* file, const size_t line, std::string const& fmt, Args... args):cinamo::Exception(file, line, fmt, args...){};
	Exception(const char* file, const size_t line, std::string const& fmt, va_list lst) throw():cinamo::Exception(file, line, fmt, lst){};
};

}}
