/*
 * CLISystem.h
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#ifndef CLISYSTEM_H_
#define CLISYSTEM_H_

#include "../nekomata/system/System.h"
#include "../nekomata/logging/Logging.h"

namespace cli {

class CLISystem: public nekomata::system::System {
public:
	CLISystem(nekomata::logging::Logger& log);
	virtual ~CLISystem();
};

} /* namespace cli */
#endif /* CLISYSTEM_H_ */
