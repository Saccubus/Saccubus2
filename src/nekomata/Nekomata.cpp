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
:system(system), log(log), machine(log, system), timeline(), currentTime(0)
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
void Nekomata::parseTimelineStream(std::istream& stream, const std::string& name)
{
	timeline.merge(parser::Parser::fromStream(stream, name)->parseTimeline());
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
	if(time < currentTime){
		log.e(TAG, 0, "Sorry, rewind operation is not supported yet!");
	}else{
		timeline::TimeLine::Iterator it = timeline.begin(currentTime);
		timeline::TimeLine::Iterator const end = timeline.end(time);
		for(; it!=end;++it){
			//TODO: 実際にseekする
			const float playTime = it->getTime();
			shared_ptr<const tree::ExprNode> node = it->getNode();
			log.t(TAG, &node->location(), "Now evaluating node at %f", playTime);
			machine.eval(node.get());
		}
		currentTime = time;
	}
}


}
