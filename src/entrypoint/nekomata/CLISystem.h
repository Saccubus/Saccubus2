/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <iostream>
#include <cinamo/Handler.h>
#include <nekomata/logging/Logging.h>
#include <nekomata/system/System.h>

namespace cli {
using cinamo::Handler;

class CLISystem: public nekomata::system::System {
private:
	std::ostream& _stream;
public:
	CLISystem(nekomata::logging::Logger& log, std::ostream& _stream);
	virtual ~CLISystem();
public:
	std::ostream& stream(){return _stream;};
	virtual Handler<nekomata::system::Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
};

class CLILabel : public nekomata::system::Label
{
private:
	CLISystem& system;
public:
	CLILabel(CLISystem& system):Label(system), system(system){};
	virtual ~CLILabel() noexcept = default;
public:
	virtual void onChanged();
};

}
