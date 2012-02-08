/*
 * Logging.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>

namespace logging
{

class Dumper;
class Dumpable;
class Location;

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
		filename(fname), lineNo(lineNo), colNo(colNo)
	{}
	Location(const Location& loc):
		filename(loc.filename), lineNo(loc.lineNo), colNo(loc.colNo)
	{}
	virtual ~Location(){};
};

class Dumper
{
public:
	Dumper();
	virtual ~Dumper();
};

}

#endif /* LOGGING_H_ */
