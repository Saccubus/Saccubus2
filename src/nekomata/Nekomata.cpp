/*
 * Nekomata.cpp
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#include "Nekomata.h"

namespace nekomata {

Nekomata::Nekomata(Adapter& adapter, logging::Logger& log)
:adapter(adapter), log(log), system(adapter), machine(log, system)
{
}

Nekomata::~Nekomata() {
	// TODO Auto-generated destructor stub
}

}
