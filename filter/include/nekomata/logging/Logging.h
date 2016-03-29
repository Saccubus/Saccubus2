/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <memory>
#include <cstdarg>
#include <cinamo/Logger.h>

#include <nekomata/classdefs.h>

namespace nekomata{
namespace logging{

class Logger
{
private:
	cinamo::Logger& spirit_;
public:
	Logger(cinamo::Logger& spirit);
	virtual ~Logger();
	void e(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void e(Exception& exception);
	void w(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void d(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void i(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void v(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void t(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
private:
	void msg(enum cinamo::Logger::Level level, const std::string& tag, const tree::Location* loc, const std::string& str, va_list list);
};

class Dumper
{
public:
	Dumper(std::ostream& stream);
	virtual ~Dumper();
	void printName(const std::string& name);
	void printName(const std::string& name, const tree::Location& loc);
	void printDumpable(const std::string& name, const std::shared_ptr<const Dumpable> member);
	void printDumpableList(const std::string& name, const std::vector<std::shared_ptr<const Dumpable> >& memberList);
	void printDumpableList(const std::string& name, const std::map<std::string, std::shared_ptr<const Dumpable> >& memberList);
	void print(const std::string& name, const std::string& member);
	void print(const std::string& name, const double member);
	void print(const std::string& name, const bool member);
private:
	int indent;
	std::ostream& stream;
	void startLine();
	void in();
	void out();
};

}}
