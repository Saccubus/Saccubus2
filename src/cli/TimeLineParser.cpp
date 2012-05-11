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

#include <nekomata/logging/Exception.h>
#include <nekomata/parser/Parser.h>
#include <cstdlib>
#include "TimeLineParser.h"
#include "../nekomata/tree/Node.h"
#include "../nekomata/util/StringUtil.h"

namespace cli{

TimeLineParser::TimeLineParser(std::istream& stream, const std::string& filename)
:stream(stream), filename(filename){
}

TimeLineParser::~TimeLineParser() {
}

void TimeLineParser::parseLine(std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Message>, std::less<float> >& timeLine, const std::string& line, int lineno)
{
	if(line.size() <= 0){
		return;
	}
	const size_t firstSep = line.find(':');
	if(firstSep == std::string::npos){
		throw nekomata::logging::Exception(__FILE__, __LINE__, "failed to parse timeline: \"%s\"", line.c_str());
	}
	const size_t secondSep = line.find(':', firstSep+1);
	if(secondSep == std::string::npos){
		throw nekomata::logging::Exception(__FILE__, __LINE__, "failed to parse timeline: \"%s\"", line.c_str());
	}
	const std::string timeStr(line.substr(0, firstSep));
	const char* timeCstr = timeStr.c_str();
	char* endPtr=0;
	const float time = std::strtof(timeCstr, &endPtr);
	if(!endPtr && *endPtr != '\0'){
		throw nekomata::logging::Exception(__FILE__, __LINE__, "failed to parse time string: \"%s\", invalid sequence: \"%s\"", timeCstr, endPtr);
	}
	const std::string mail(line.substr(firstSep+1, secondSep));
	std::string message(line.substr(secondSep+1));
	if (message.at(message.size()-1) == '\n') message.erase(message.size()-1);
	if (message.at(message.size()-1) == '\r') message.erase(message.size()-1);
	switch(message.at(0))
	{
	case '\%':
	{
		std::tr1::shared_ptr<const nekomata::system::Comment> com(new nekomata::system::Comment(message.substr(1), time, true, mail, false, false, 0xffffff, 30, 0));
		timeLine.insert(std::pair<float, std::tr1::shared_ptr<const nekomata::system::Comment> >(time, com));
		break;
	}
	case '/':
	{
		std::tr1::shared_ptr<const nekomata::tree::Node> node(nekomata::parser::Parser::fromString(message.substr(1), filename, lineno)->parseProgram());
		std::tr1::shared_ptr<const nekomata::system::Message> com(new nekomata::system::Script(time, node));
		timeLine.insert(std::pair<float, std::tr1::shared_ptr<const nekomata::system::Message> >(time, com));
		break;
	}
	default:
	{
		std::tr1::shared_ptr<const nekomata::system::Message> com(new nekomata::system::Comment(message, time, true, mail, false, false, 0xffffff, 30, 0));
		timeLine.insert(std::pair<float, std::tr1::shared_ptr<const nekomata::system::Message> >(time, com));
		break;
	}
	}
}

std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Message>, std::less<float> > TimeLineParser::parse()
{
	std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Message>, std::less<float> > timeLine;
	std::string buf;
	int count = 0;
	while(stream && std::getline(stream, buf)){
		while(buf.size() > 0 && (buf.at(buf.size()-1)=='\r' || buf.at(buf.size()-1)=='\n')){
			buf=buf.substr(0, buf.size()-1);
		}
		while(buf.size() > 0 && (buf.at(0)=='\r' || buf.at(0)=='\n')){
			buf=buf.substr(1);
		}
		this->parseLine(timeLine,buf, ++count);
	}
	return timeLine;
}

}
