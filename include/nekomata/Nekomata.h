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
#include <cfloat>

#include "logging/Logging.h"
#include "classdefs.h"

namespace nekomata {

const std::string PROGRAM_NAME("Nekomata");
const std::string PROGRAM_VERSION("ver 1.00");

class Nekomata {
private:
	system::System& system;
	logging::Logger& log;
	machine::Machine* const machine;
	float currentTime;
public:
	explicit Nekomata(system::System& system, logging::Logger& log);
	virtual ~Nekomata();
public:
	void seek(float time=FLT_MAX);
};

}
#endif /* NEKOMATA_H_ */
