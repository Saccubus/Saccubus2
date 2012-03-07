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
#include "../classdefs.h"
#ifdef ERROR
#undef ERROR
#endif

namespace nekomata{
namespace logging
{

class Dumpable{
protected:
	Dumpable(){};
	virtual ~Dumpable(){};
public:
	virtual void dump(Dumper& dumper) const = 0;
};


class Location{
private:
	const std::string filename;
	const int lineNo;
	const int colNo;
	const std::string origin;
public:
	Location(const std::string& fname, int lineNo, int colNo, const std::string& origin):
		filename(fname), lineNo(lineNo), colNo(colNo), origin(origin)
	{}
	Location(const Location& loc):
		filename(loc.filename), lineNo(loc.lineNo), colNo(loc.colNo), origin(loc.origin)
	{}
	Location()
		: filename("<null>"), lineNo(-1), colNo(-1), origin("<null>")
	{};
	virtual ~Location(){};
    const int getColNo() const{return colNo;}
    const std::string getFilename() const{return filename;}
    const int getLineNo() const{return lineNo;}
    const std::string getOrigin() const{return origin;}
};

#undef ERROR
class Logger
{
public:
	enum Level{
		TRACE=0,
		VERBOSE=1,
		DEBUG=2,
		WARNING=3,
		ERROR=4,
	};
public:
	Logger(std::ostream& stream, enum Level level = VERBOSE);
	virtual ~Logger();
	void e(const std::string& tag, const Location* loc, const std::string& str, ...);
	void e(Exception& exception);
	void w(const std::string& tag, const Location* loc, const std::string& str, ...);
	void d(const std::string& tag, const Location* loc, const std::string& str, ...);
	void v(const std::string& tag, const Location* loc, const std::string& str, ...);
	void t(const std::string& tag, const Location* loc, const std::string& str, ...);
private:
	void msg(enum Level level, const std::string& tag, const Location* loc, const std::string& str, va_list list);
	enum Level level;
	std::ostream& stream;
};

class Dumper
{
public:
	Dumper(std::ostream& stream);
	virtual ~Dumper();
	void printName(const std::string& name);
	void printName(const std::string& name, const Location& loc);
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

}
}

#endif /* LOGGING_H_ */
