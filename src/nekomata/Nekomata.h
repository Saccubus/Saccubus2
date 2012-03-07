/*
 * Nekomata.h
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#ifndef NEKOMATA_H_
#define NEKOMATA_H_
#include <iostream>
#include <vector>

#include "classdefs.h"
#include "TimeLine.h"
#include "logging/Logging.h"
#include "machine/Machine.h"

namespace nekomata {

static const std::string PROGRAM_NAME;
static const std::string PROGRAM_VERSION;

class Nekomata {
private:
	system::System& system;
	logging::Logger& log;
	machine::Machine machine;
	TimeLine<const tree::ExprNode> scriptLine;
	TimeLine<const system::Comment> commentLine;
	float currentTime;
public:
	explicit Nekomata(system::System& system, logging::Logger& log);
	virtual ~Nekomata();
public:
	void parseTimelineStr(const std::string& str);
	void parseTimelineFile(const std::string& filename);
	void parseTimelineStream(std::istream& stream, const std::string& name="<stream>");
	void parseProgram(float time, const std::string& str);
	void dump(std::ostream& stream);
public:
	float getLastTime();
	void seek(float time);
};

}
#endif /* NEKOMATA_H_ */
