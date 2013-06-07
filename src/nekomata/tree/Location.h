/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>

namespace nekomata{
namespace tree{

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

}}
