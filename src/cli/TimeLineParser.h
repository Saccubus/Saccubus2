/*
 * TimeLineParser.h
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#ifndef TIMELINEPARSER_H_
#define TIMELINEPARSER_H_

#include <fstream>
#include <string>
#include <iostream>
#include <nekomata/system/System.h>

namespace cli{

class TimeLineParser {
	std::istream& stream;
	const std::string filename;
public:
	TimeLineParser(std::istream& stream, const std::string& filename="<UNSPECIFIED>");
	virtual ~TimeLineParser();
private:
	void parseLine(std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Comment>, std::less<float> >& timeLine, const std::string& line);
public:
	std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Comment>, std::less<float> > parse();
};

}
#endif /* TIMELINEPARSER_H_ */
