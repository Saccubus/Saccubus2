/**
 * Saccubus
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

#include "MockSystem.h"
#include <nekomata/logging/Logging.h>

namespace saccubus {
namespace mock {

MockSystem::MockSystem()
:System(*(new nekomata::logging::Logger(std::cout, nekomata::logging::Logger::WARNING_)))
{

}

MockSystem::~MockSystem() {
	delete &log;
}

std::tr1::shared_ptr<const nekomata::system::Comment> MockSystem::nextComment()
{
	return std::tr1::shared_ptr<const nekomata::system::Comment>();
}
}}
