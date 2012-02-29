/*
 * System.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include "../Nekomata.h"
#include "System.h"
#include "../object/Object.h"
#include "../object/Heap.h"
#include <tr1/memory>

namespace nekomata{
namespace system {

#define SET(name, _default) this->name(_default);

System::System()
{
	// TODO Auto-generated constructor stub

}

System::~System() {
	// TODO Auto-generated destructor stub
}

std::tr1::shared_ptr<Shape> System::drawShape(double x, double y, double z, std::string shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover)
{

}
std::tr1::shared_ptr<Chat> System::drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover)
{

}
void System::commentTrigger(float const timer, const tree::Node* then)
{

}
void System::timer(float const timer, const tree::Node* then)
{

}
void System::jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow)
{

}
void System::jumpCancel()
{

}
void System::seek(double vpos, const std::string& msg)
{

}
void System::addMarker(const std::string& name, double vpos)
{

}
double System::getMarker(const std::string& name)
{

}
std::tr1::shared_ptr<Sum> System::sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial)
{

}
std::tr1::shared_ptr<SumResult> System::showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<std::tr1::shared_ptr<Sum> > sum)
{

}
std::tr1::shared_ptr<Replace> System::replace(const std::string& src, const std::string& dst, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos)
{

}
double System::screenWidth()
{

}
double System::screenHeight()
{

}
std::tr1::shared_ptr<Button> System::addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden)
{

}
double System::playStartTime()
{

}
void System::BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume)
{

}
void System::playBGM(int id)
{

}
void System::stopBGM(int id)
{

}
void System::addAtPausePoint(double vpos, double wait)
{

}
void System::addPostRoute(const std::string& match, const std::string& id, const std::string& button)
{

}
void System::CM(const std::string& id, double time, bool pause, const std::string& link, double volume)
{

}
void System::playCM(int id)
{

}


}}
