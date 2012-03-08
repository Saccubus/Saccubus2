/*
 * CLISystem.cpp
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#include "CLISystem.h"
#include "../nekomata/util/StringUtil.h"

namespace cli {

void CLILabel::onChanged()
{
	system.stream() << nekomata::util::format("[label][%8 .2f] %s", this->system.currentTime(), text().c_str()) << std::endl;
}

CLISystem::CLISystem(nekomata::logging::Logger& log, std::ostream& _stream)
:System(log)
,_stream(_stream)
{
	// TODO Auto-generated constructor stub

}

CLISystem::~CLISystem() {
	// TODO Auto-generated destructor stub
}

nekomata::util::Handler<nekomata::system::Label> CLISystem::drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover)
{
	stream() << nekomata::util::format("[label][%8 .2f] %s", this->currentTime(), text.c_str()) << std::endl;
	nekomata::util::Handler<nekomata::system::Label> label(new CLILabel(*this));
	label->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return label;
}

nekomata::system::Comment CLISystem::findFirstComment(const int objColor, const double from, const double to)
{
	nekomata::TimeLine<nekomata::system::Comment>::Iterator it = this->commentLine.begin(from);
	nekomata::TimeLine<nekomata::system::Comment>::Iterator end = this->commentLine.end(to);
	for(; it != end; ++it){
		if(it->getData()->objColor() != objColor){
			it->getData()->objColor(objColor);
			return *(it->getData().get());
		}
	}
	return nekomata::system::Comment();
}


} /* namespace cli */
