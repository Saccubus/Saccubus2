/*
 * Niwango.cpp
 *
 *  Created on: 2012/02/26
 *      Author: psi
 */

#include "../nekomata/Nekomata.h"
#include "./CLIAdapter.h"

namespace cli{

int _main(int argc, char** args){

	CLIAdapter* adapter = 0;
	nekomata::logging::Logger logger(std::cout);
	nekomata::Nekomata(*adapter, logger);

	return 0;
}

}

