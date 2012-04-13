/*
 * CLISystem.cpp
 *
 *  Created on: 2012/02/29
 *      Author: psi
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

CLISystem::CLISystem(nekomata::logging::Logger& log, std::ostream& _stream, const std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Comment> >& commentLine)
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

std::tr1::shared_ptr<const nekomata::system::Comment> CLISystem::nextComment()
{
	if(_currentComment != commentLine.end()){
		return (_currentComment++)->second;
	}else{
		return std::tr1::shared_ptr<const nekomata::system::Comment>();
	}
}


} /* namespace cli */
