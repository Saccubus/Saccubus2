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

#include <nekomata/parser/Parser.h>
#include "CLISystem.h"
#include "../nekomata/util/StringUtil.h"

namespace cli {

void CLILabel::onChanged()
{
	Label::onChanged();
	system.stream() << nekomata::util::format("[Label][% 8.2f] %s", this->system.currentTime(), text().c_str()) << std::endl;
}

CLISystem::CLISystem(nekomata::logging::Logger& log, std::ostream& _stream, const std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Message> >& commentLine)
:System(log)
,_stream(_stream)
, commentLine(commentLine.begin(), commentLine.end())
{
	_currentComment = this->commentLine.begin();
}

CLISystem::~CLISystem() {
}

nekomata::util::Handler<nekomata::system::Label> CLISystem::drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover)
{
	stream() << nekomata::util::format("[Label][% 8.2f] %s", this->currentTime(), text.c_str()) << std::endl;
	nekomata::util::Handler<nekomata::system::Label> label(new CLILabel(*this));
	label->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return label;
}

std::tr1::shared_ptr<const nekomata::system::Message> CLISystem::nextMessage()
{
	if(_currentComment != commentLine.end()){
		return (_currentComment++)->second;
	}else{
		return std::tr1::shared_ptr<const nekomata::system::Comment>();
	}
}


} /* namespace cli */
