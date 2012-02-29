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

using namespace std::tr1;

static const std::string TAG("System");

System::System(logging::Logger& log)
:log(log)
{
}

System::~System() {
	// TODO Auto-generated destructor stub
}

shared_ptr<Shape> System::drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover)
{
	log.t(TAG, 0,
			"drawShape(x: %f, y: %f, z: %f, shape: %s, width: %f, height: %f, color:%x, visible: %d, pos: %s, mask: %d, commentmask: %d, alpha: %f, rotation:%f, mover: %s",
			x, y, z, shape.c_str(), width, height, color, visible, pos.c_str(), mask, commentmask, alpha, rotation, mover.c_str()
			);
	shared_ptr<Shape> _shape(new Shape(*this));
	_shape->load(x, y, z, shape, width, height, color, visible, pos, mask, commentmask, alpha, rotation, mover);
	return _shape;
}
shared_ptr<Chat> System::drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover)
{
	log.t(TAG, 0,
			"drawText(%s)",
			text.c_str()
			);
	shared_ptr<Chat> _chat(new Chat(*this));
	_chat->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return _chat;
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
shared_ptr<Sum> System::sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial)
{
	shared_ptr<Sum> _sum(new Sum(*this));
	_sum->load(x, y, size, color, visible, enabled, pos, asc, unit, buttononly, words, partial);
	return _sum;
}
shared_ptr<SumResult> System::showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<shared_ptr<Sum> > sum)
{
	shared_ptr<SumResult> _sumResult(new SumResult(*this));
	_sumResult->load(x, y, color, visible, pos, unit, asc, sum);
	return _sumResult;
}
shared_ptr<Replace> System::replace(const std::string& src, const std::string& dst, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos)
{
	shared_ptr<Replace> _replace(new Replace(*this));
	_replace->load(src, dst, enabled, target, fill, partial, color, size, pos);
	return _replace;
}
double System::screenWidth()
{

}
double System::screenHeight()
{

}
shared_ptr<Button> System::addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden)
{
	shared_ptr<Button> _button(new Button(*this));
	_button->load(message, mail, vpos, commes, commail, comvisible, limit, hidden);
	return _button;
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
