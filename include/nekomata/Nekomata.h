/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
public:
	explicit Nekomata(system::System& system, logging::Logger& log);
	virtual ~Nekomata();
public:
	void queueMessage(std::tr1::shared_ptr<const system::Message> msg);
	void seek(float time);
	float currentTime();
};

}
#endif /* NEKOMATA_NEKOMATA_H_ */
