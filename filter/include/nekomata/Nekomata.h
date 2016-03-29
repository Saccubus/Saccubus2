/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
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
public:
	explicit Nekomata(system::System& system, logging::Logger& log);
	virtual ~Nekomata();
public:
	void queueMessage(std::shared_ptr<const system::Message> msg);
	void seek(float time);
	float currentTime();
};

}
