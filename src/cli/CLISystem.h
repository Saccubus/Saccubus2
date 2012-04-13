/*
 * CLISystem.h
 *
 *  Created on: 2012/02/29
 *      Author: psi
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
	std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Comment>, std::less<float> > commentLine;
	std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Comment>, std::less<float> >::const_iterator _currentComment;
public:
	CLISystem(nekomata::logging::Logger& log, std::ostream& _stream, const std::multimap<float, std::tr1::shared_ptr<const nekomata::system::Comment> >& commentLine);
	virtual ~CLISystem();
public:
	std::ostream& stream(){return _stream;};
	virtual nekomata::util::Handler<nekomata::system::Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
	virtual std::tr1::shared_ptr<const nekomata::system::Comment> nextComment();
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
