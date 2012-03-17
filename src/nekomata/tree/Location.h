/*
 * Location.h
 *
 *  Created on: 2012/03/17
 *      Author: psi
 */

#ifndef LOCATION_H_
#define LOCATION_H_

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
#endif /* LOCATION_H_ */
