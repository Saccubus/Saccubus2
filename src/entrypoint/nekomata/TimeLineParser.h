/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
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
	void parseLine(std::multimap<float, std::shared_ptr<const nekomata::system::Message>, std::less<float> >& timeLine, const std::string& line, int lineno);
public:
	std::multimap<float, std::shared_ptr<const nekomata::system::Message>, std::less<float> > parse();
};

}
