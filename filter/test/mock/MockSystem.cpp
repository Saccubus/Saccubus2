/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "MockSystem.h"
#include <nekomata/logging/Logging.h>
#include "../TestCommon.h"

namespace samock {

MockSystem::MockSystem()
:System(*(new nekomata::logging::Logger(log_trace)))
{

}

MockSystem::~MockSystem() {
	delete &log;
}

std::shared_ptr<const nekomata::system::Comment> MockSystem::nextComment()
{
	return std::shared_ptr<const nekomata::system::Comment>();
}

}
