/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <string>
#include <nekomata/Nekomata.h>
#include <nekomata/parser/Parser.h>
#include <nekomata/system/System.h>
#include <nekomata/logging/Logging.h>
#include "machine/Machine.h"
#include "tree/Node.h"

namespace nekomata {

static const std::string TAG("Nekomata");

Nekomata::Nekomata(system::System& system, logging::Logger& log)
:system(system)
,log(log)
,machine(new machine::Machine(log, system))
{
}

Nekomata::~Nekomata() {
	delete machine;
}

void Nekomata::seek(float time)
{
	if(time < currentTime()){
		log.e(TAG, 0, "Sorry, rewind operation is not supported yet! now: %f, seeked time: %f", currentTime(), time);
	}else{
		system.seek(*machine, currentTime(), time);
	}
}

float Nekomata::currentTime()
{
	return system.currentTime();
}

void Nekomata::queueMessage(std::shared_ptr<const nekomata::system::Message> msg)
{
	system.queueMessage(msg);
}

}
