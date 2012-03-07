/*
 * CLISystem.h
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#ifndef CLISYSTEM_H_
#define CLISYSTEM_H_

#include "../nekomata/TimeLine.h"
#include "../nekomata/system/System.h"
#include "../nekomata/logging/Logging.h"

namespace cli {

class CLISystem: public nekomata::system::System {
private:
	nekomata::TimeLine<const nekomata::system::Comment> commentLine;
public:
	CLISystem(nekomata::logging::Logger& log);
	virtual ~CLISystem();
public:
	virtual float triggerComment(nekomata::machine::Machine& machine, const double from, const double to);
	virtual nekomata::TimeLine<const nekomata::system::Comment>* getCommentTimeLine(){ return &commentLine; };
};

}
#endif /* CLISYSTEM_H_ */
