/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */
#pragma once
#include <nekomata/system/System.h>

namespace nekomata {

class MockSystem: public nekomata::system::System {
public:
	MockSystem(logging::Logger& log);
	virtual ~MockSystem();
};

}
