/*
 * Nekomata.cpp
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#include <string>
#include "Nekomata.h"
#include "tree/Node.h"
#include "parser/Parser.h"
#include "system/System.h"
#include "logging/Logging.h"

using namespace std::tr1;

namespace nekomata {

/*
const std::string PROGRAM_NAME("Nekomata");
const std::string PROGRAM_VERSION("ver 1.00");
*/
static const std::string TAG("TOP");

Nekomata::Nekomata(system::System& system, logging::Logger& log)
:system(system), log(log), machine(log, system), scriptLine(), currentTime(0)
{
}

Nekomata::~Nekomata() {
}

void Nekomata::parseTimelineStr(const std::string& str)
{
	parser::Parser::fromString(str)->parseTimeline(&scriptLine, system.getCommentTimeLine());
}
void Nekomata::parseTimelineFile(const std::string& filename)
{
	parser::Parser::fromFile(filename)->parseTimeline(&scriptLine, system.getCommentTimeLine());
}
void Nekomata::parseTimelineStream(std::istream& stream, const std::string& name)
{
	parser::Parser::fromStream(stream, name)->parseTimeline(&scriptLine, system.getCommentTimeLine());
}

void Nekomata::parseProgram(float time, const std::string& str)
{
	scriptLine.insertLast(time, parser::Parser::fromString(str)->parseProgram());
}

void Nekomata::dump(std::ostream& stream)
{
	nekomata::logging::Dumper dumper(stream);

	TimeLine<const tree::ExprNode>::Iterator it = scriptLine.begin();
	TimeLine<const tree::ExprNode>::Iterator const end = scriptLine.end();
	for(; it != end; ++it){
		dumper.printName("Script");
		dumper.print("Time: ", it->getTime());
		dumper.printDumpable("Node: ", it->getData());
	}
}

float Nekomata::getLastTime()
{
	return std::max(scriptLine.getLastTime(), system.getLastCommentTime());
}
void Nekomata::seek(float time)
{
	if(time < currentTime){
		log.e(TAG, 0, "Sorry, rewind operation is not supported yet!");
	}else{
		TimeLine<const tree::ExprNode>::Iterator it = scriptLine.begin(currentTime);
		TimeLine<const tree::ExprNode>::Iterator const end = scriptLine.end(time);
		for(; it!=end;++it){
			const float playTime = it->getTime();
			{
				system.seek(machine, currentTime, playTime);
			}
			{
				shared_ptr<const tree::ExprNode> node = it->getData();
				log.t(TAG, &node->location(), "Now evaluating node at %f", playTime);
				machine.eval(node.get());
			}
			currentTime = playTime;
		}
		system.seek(machine, currentTime, time);
		currentTime = time;
	}
}


}
