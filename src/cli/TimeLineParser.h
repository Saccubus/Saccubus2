/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	void parseLine(std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Message>, std::less<float> >& timeLine, const std::string& line);
public:
	std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Message>, std::less<float> > parse();
};

}
#endif /* TIMELINEPARSER_H_ */
