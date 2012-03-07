/*
 * CLISystem.cpp
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#include "CLISystem.h"

namespace cli {

CLISystem::CLISystem(nekomata::logging::Logger& log)
:System(log)
{
	// TODO Auto-generated constructor stub

}

CLISystem::~CLISystem() {
	// TODO Auto-generated destructor stub
}

float CLISystem::triggerComment(nekomata::machine::Machine& machine, const double from, const double to)
{
	nekomata::TimeLine<const nekomata::system::Comment>::Iterator it = this->commentLine.begin(from);
	nekomata::TimeLine<const nekomata::system::Comment>::Iterator end = this->commentLine.end(to);
	float time = NAN;
	for(;it != end;++it){
		dispatchCommentTrigger(machine, it->getData().get());
		time = it->getData()->vpos();
	}
	return time;
}


} /* namespace cli */
