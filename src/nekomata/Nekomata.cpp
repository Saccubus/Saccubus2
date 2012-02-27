/*
 * Nekomata.cpp
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#include "Nekomata.h"

namespace nekomata {

Nekomata::Nekomata(system::System& system, logging::Logger& log)
:system(system), log(log), machine(log, system)
{
}

Nekomata::~Nekomata() {
	// TODO Auto-generated destructor stub
}

}
