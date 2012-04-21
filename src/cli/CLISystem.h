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

#ifndef CLISYSTEM_H_
#define CLISYSTEM_H_

#include <iostream>
#include <nekomata/logging/Logging.h>
#include <nekomata/system/System.h>

namespace cli {


class CLISystem: public nekomata::system::System {
private:
	std::ostream& _stream;
public:
	CLISystem(nekomata::logging::Logger& log, std::ostream& _stream);
	virtual ~CLISystem();
public:
	std::ostream& stream(){return _stream;};
	virtual nekomata::util::Handler<nekomata::system::Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
};

class CLILabel : public nekomata::system::Label
{
private:
	CLISystem& system;
public:
	CLILabel(CLISystem& system):Label(system), system(system){};
	virtual ~CLILabel(){};
public:
	virtual void onChanged();
};

}
#endif /* CLISYSTEM_H_ */
