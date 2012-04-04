/*
 * Logging.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <tr1/memory>
#include <cstdarg>

#include <nekomata/classdefs.h>

namespace nekomata{
namespace logging{

class Logger
{
public:
	enum Level{
		TRACE_=0,
		VERBOSE_=1,
		DEBUG_=2,
		INFO_=3,
		WARNING_=4,
		ERROR_=5,
	};
public:
	Logger(std::ostream& stream, enum Level level = VERBOSE_);
	virtual ~Logger();
	void e(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void e(Exception& exception);
	void w(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void d(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void i(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void v(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
	void t(const std::string& tag, const tree::Location* loc, const std::string& str, ...);
private:
	void msg(enum Level level, const std::string& tag, const tree::Location* loc, const std::string& str, va_list list);
	enum Level level;
	std::ostream& stream;
};

class Dumper
{
public:
	Dumper(std::ostream& stream);
	virtual ~Dumper();
	void printName(const std::string& name);
	void printName(const std::string& name, const tree::Location& loc);
	void printDumpable(const std::string& name, const std::tr1::shared_ptr<const Dumpable> member);
	void printDumpableList(const std::string& name, const std::vector<std::tr1::shared_ptr<const Dumpable> >& memberList);
	void printDumpableList(const std::string& name, const std::map<std::string, std::tr1::shared_ptr<const Dumpable> >& memberList);
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

#endif /* LOGGING_H_ */
