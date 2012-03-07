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

nekomata::system::Comment CLISystem::findFirstComment(const int objColor, const double from, const double to)
{
	nekomata::TimeLine<nekomata::system::Comment>::Iterator it = this->commentLine.begin(from);
	nekomata::TimeLine<nekomata::system::Comment>::Iterator end = this->commentLine.end(to);
	for(; it != end; ++it){
		if(it->getData()->objColor() != objColor){
			it->getData()->objColor(objColor);
			return *(it->getData().get());
		}
	}
	return nekomata::system::Comment();
}


} /* namespace cli */
