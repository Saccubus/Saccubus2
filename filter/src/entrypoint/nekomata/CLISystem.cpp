/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <nekomata/parser/Parser.h>
#include <cinamo/String.h>
#include "CLISystem.h"

namespace cli {

void CLILabel::onChanged()
{
	Label::onChanged();
	system.stream() << cinamo::format("[Label][% 8.2f] %s", this->system.currentTime(), text().c_str()) << std::endl;
}

CLISystem::CLISystem(nekomata::logging::Logger& log, std::ostream& _stream)
:System(log)
,_stream(_stream)
{
}

CLISystem::~CLISystem() {
}

Handler<nekomata::system::Label> CLISystem::drawText(std::string const& text, double x, double y, double z, double size, std::string const& pos, unsigned int color, bool bold, bool visible, std::string const& filter, double alpha, std::string const& mover)
{
	stream() << cinamo::format("[Label][% 8.2f] %s", this->currentTime(), text.c_str()) << std::endl;
	Handler<nekomata::system::Label> label(new CLILabel(*this));
	label->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return label;
}

}
