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

#include "machine/Machine.h"
#include "system/System.h"
#include "logging/Logging.h"

namespace nekomata {

class Nekomata {
private:
	system::System& system;
	logging::Logger& log;
	machine::Machine machine;
public:
	explicit Nekomata(system::System& system, logging::Logger& log);
	virtual ~Nekomata();
public:
	void parseTimelineStr(std::string& str);
	void parseTimelineFile(std::string& filename);
	void parseProgram(float time, std::string& str);
public:
	float getLastTime();
	void seek(float time);
};

}
#endif /* NEKOMATA_H_ */
