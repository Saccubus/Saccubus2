/*
 * CLISystem.h
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#ifndef CLISYSTEM_H_
#define CLISYSTEM_H_

#include <iostream>
#include "../nekomata/TimeLine.h"
#include "../nekomata/system/System.h"
#include "../nekomata/logging/Logging.h"

namespace cli {


class CLISystem: public nekomata::system::System {
private:
	std::ostream& _stream;
	nekomata::TimeLine<nekomata::system::Comment> commentLine;
public:
	CLISystem(nekomata::logging::Logger& log, std::ostream& _stream);
	virtual ~CLISystem();
public:
	std::ostream& stream(){return _stream;};
	virtual nekomata::util::Handler<nekomata::system::Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
	virtual nekomata::system::Comment findFirstComment(const int objColor, const double from, const double to);
	virtual nekomata::TimeLine<nekomata::system::Comment>* getCommentTimeLine(){ return &commentLine; };
	virtual float getLastCommentTime() {return commentLine.size() > 0 ? commentLine.getLastTime() : -1;};
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
