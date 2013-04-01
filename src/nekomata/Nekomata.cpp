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
