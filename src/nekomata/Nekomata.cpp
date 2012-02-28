/*
 * Nekomata.cpp
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#include "Nekomata.h"
#include "tree/Node.h"
#include "parser/Parser.h"
#include "system/System.h"
#include "logging/Logging.h"

namespace nekomata {

Nekomata::Nekomata(system::System& system, logging::Logger& log)
:system(system), log(log), machine(log, system), timeline()
{
}

Nekomata::~Nekomata() {
	// TODO Auto-generated destructor stub
}

void Nekomata::parseTimelineStr(const std::string& str)
{
	timeline.merge(parser::Parser::fromString(str)->parseTimeline());
}
void Nekomata::parseTimelineFile(const std::string& filename)
{
	timeline.merge(parser::Parser::fromFile(filename)->parseTimeline());
}
void Nekomata::parseProgram(float time, const std::string& str)
{
	timeline.insertLast(time, parser::Parser::fromString(str)->parseProgram());
}
float Nekomata::getLastTime()
{
	return timeline.getLastTime();
}
void Nekomata::seek(float time)
{

}


}
