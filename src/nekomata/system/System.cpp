/*
 * System.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include <tr1/memory>
#include <cmath>
#include "System.h"
#include "../logging/Logging.h"
#include "../tree/Node.h"
#include "../machine/Machine.h"
#include "../object/Object.h"
#include "../object/SystemObject.h"
#include "../object/Heap.h"

namespace nekomata{
namespace system {

using namespace std::tr1;

static const std::string TAG("System");

System::System(logging::Logger& log)
:_currentTime(0), color(0), log(log)
{
}

System::~System() {
	// TODO Auto-generated destructor stub
}

util::Handler<Shape> System::drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover)
{
	log.v(TAG, 0,
			"drawShape(x: %f, y: %f, z: %f, shape: %s, width: %f, height: %f, color:%x, visible: %d, pos: %s, mask: %d, commentmask: %d, alpha: %f, rotation:%f, mover: %s",
			x, y, z, shape.c_str(), width, height, color, visible, pos.c_str(), mask, commentmask, alpha, rotation, mover.c_str()
			);
	util::Handler<Shape> _shape(new Shape(*this));
	_shape->load(x, y, z, shape, width, height, color, visible, pos, mask, commentmask, alpha, rotation, mover);
	return _shape;
}
util::Handler<Label> System::drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover)
{
	log.v(TAG, 0,
			"drawText(text:%s , x: %f, y: %f, z: %f, size: %f, pos: %s, color: %d, bold: %d, visible: %d, filter: %s, alpha: %f, mover: %s)",
			text.c_str(), x, y, z, size, pos.c_str(), color, bold, visible, filter.c_str(), alpha, mover.c_str()
			);
	util::Handler<Label> _label(new Label(*this));
	_label->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return _label;
}
void System::commentTrigger(float const timer, const tree::Node* then)
{
	log.v(TAG, 0,
			"commentTrigger(timer: %f, node: (%d, %d in %s))",
			timer, then->location().getLineNo(), then->location().getColNo(), then->location().getFilename().c_str()
			);
	std::tr1::shared_ptr<EventEntry> evt(new EventEntry(currentTime(), currentTime()+timer, then));
	this->ctrigLine.insertLast(currentTime()+timer, evt);
}
void System::timer(float const timer, const tree::Node* then)
{
	log.v(TAG, 0,
			"timer(timer: %f, node: (%d, %d in %s))",
			timer, then->location().getLineNo(), then->location().getColNo(), then->location().getFilename().c_str()
			);
	std::tr1::shared_ptr<EventEntry> evt(new EventEntry(currentTime()+timer, currentTime()+timer, then));
	this->timerLine.insertLast(timer+currentTime(), evt);
}
void System::jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow)
{
	log.v(TAG, 0,
			"jump(id:%s , msg:%s , from: %d, length: %d, _return: %d, returnmsg: %s,newwindow: %d)",
			id.c_str(), msg.c_str(), from, length, _return, returnmsg.c_str(),newwindow
			);

}
void System::jumpCancel()
{
	log.v(TAG, 0,"jumpCancel()");
}
void System::seek(double vpos, const std::string& msg)
{
	log.v(TAG, 0,
			"seek(vpos: %f, msg: %s)",
			vpos, msg.c_str()
			);
}
void System::addMarker(const std::string& name, double vpos)
{
	log.v(TAG, 0,
			"addMarker(name: %s, vpos: %f)",
			name.c_str(), vpos
			);
	markerMap.insert(std::pair<std::string, double>(name, vpos));
}
double System::getMarker(const std::string& name)
{
	log.v(TAG, 0,
			"getMarker(name: %s)",
			name.c_str()
			);
	std::map<std::string, double>::iterator it = markerMap.find(name);
	if(it != markerMap.end()){
		return it->second;
	}else{
		return NAN;
	}
}
util::Handler<Sum> System::sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial)
{
	log.v(TAG, 0,
			"sum(x: %f, y: %f, size: %f, color: %x, visible: %d, enabled: %d, pos: %s, asc: %d, unit: %s, buttononly: %d, words: %d word(s), partial: %d)",
			x, y, size, color, visible, enabled, pos.c_str(), asc, unit.c_str(), buttononly, words.size(), partial
			);
	util::Handler<Sum> _sum(new Sum(*this));
	_sum->load(x, y, size, color, visible, enabled, pos, asc, unit, buttononly, words, partial);
	return _sum;
}
util::Handler<SumResult> System::showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<util::Handler<Sum> > sum)
{
	util::Handler<SumResult> _sumResult(new SumResult(*this));
	log.v(TAG, 0,
			"showResult(x: %f, y: %f, color: %x, visible: %d, pos: %s, asc: %d, unit: %s, sum: %ditem(s))",
			x, y, color, visible, pos.c_str(), asc, unit.c_str(), sum.size()
			);
	_sumResult->load(x, y, color, visible, pos, unit, asc, sum);
	return _sumResult;
}
util::Handler<Replace> System::replace(const std::string& src, const std::string& dst, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos)
{
	util::Handler<Replace> _replace(new Replace(*this));
	log.v(TAG, 0,
			"replace(src: %s, dst: %s, enabled: %d, target: %s, fill: %d, partial: %d, color: %x, size: %s, pos: %s)",
			src.c_str(), dst.c_str(), enabled, target.c_str(), fill, partial, color, size.c_str(), pos.c_str()
			);
	_replace->load(src, dst, enabled, target, fill, partial, color, size, pos);
	return _replace;
}
double System::screenWidth()
{
	log.v(TAG, 0,"screenWidth()");
	return 512; //DEFAULT(4:3)
}
double System::screenHeight()
{
	log.v(TAG, 0,"screenHeight()");
	return 384; //DEFAULT(4:3)
}
util::Handler<Button> System::addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden)
{
	log.v(TAG, 0,
			"addButton(message: %s, mail: %s, vpos: %f, commes: %s, commail: %s, comvisible: %d, limit: %d, hidden:%d)",
			message.c_str(), mail.c_str(), vpos, commes.c_str(), commail.c_str(), comvisible, limit, hidden
			);
	util::Handler<Button> _button(new Button(*this));
	_button->load(message, mail, vpos, commes, commail, comvisible, limit, hidden);
	return _button;
}
double System::playStartTime()
{
	log.v(TAG, 0,"playStartTime()");
	return 0;
}
void System::BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume)
{
	log.v(TAG, 0,
			"BGM(id: %s, x: %f, y: %f, width: %f, height: %f, visual: %d, volume: %f)",
			id.c_str(), x, y, width, height, visual, volume
			);
}
void System::playBGM(int id)
{
	log.v(TAG, 0,"playBGM(id: %d)", id);

}
void System::stopBGM(int id)
{
	log.v(TAG, 0,"stopBGM(id: %d)", id);
}
void System::addAtPausePoint(double vpos, double wait)
{
	log.v(TAG, 0,
			"addAtPausePoint(vpos: %f, wait: %f)",
			vpos, wait
			);

}
void System::addPostRoute(const std::string& match, const std::string& id, const std::string& button)
{
	log.v(TAG, 0,
			"addPostRoute(match: %s, id: %s, button: %s)",
			match.c_str(), id.c_str(), button.c_str()
			);

}
void System::CM(const std::string& id, double time, bool pause, const std::string& link, double volume)
{
	log.v(TAG, 0,
			"addPostRoute(id: %s, time: %f, pause: %d, link: %s, volume: %f)",
			id.c_str(), time, pause, link.c_str(), volume
	);

}
void System::playCM(int id)
{
	log.v(TAG, 0,"playCM(id: %d)", id);

}


void System::seek(machine::Machine& machine, const double from, const double to)
{
	if(currentTime() != from){
		log.e(TAG, 0, "[BUG] FIXME: time was not synchronized correctly.");
	}
	nekomata::TimeLine<EventEntry>::Iterator it = timerLine.begin(from);
	nekomata::TimeLine<EventEntry>::Iterator end = timerLine.end(to);
	const int color = nextColor();

	do{
		if(it == end){
			float ctime = triggerComment(machine, currentTime(), to);
			if(ctime != ctime){
				currentTime(to);
			}else{
				currentTime(ctime);
				it = timerLine.begin(currentTime());
				end = timerLine.end(to);
			}
		}else if(currentTime() < it->getData()->from()){
			std::tr1::shared_ptr<EventEntry> evt = it->getData();
			float ctime = triggerComment(machine, currentTime(), evt->from());
			if(ctime != ctime){
				currentTime(evt->from());
			}else{
				currentTime(ctime);
				it = timerLine.begin(currentTime());
				end = timerLine.end(to);
			}
		}else{
			std::tr1::shared_ptr<EventEntry> evt = it->getData();
			if(color != evt->color()){
				evt->color(color);
				machine.eval(evt->then());
				currentTime(evt->from());
				it = timerLine.begin(currentTime());
				end = timerLine.end(to);
			}else{
				++it;
			}
		}
	}while(it != end);
}

void System::dispatchCommentTrigger(machine::Machine& machine, const Comment* comment)
{
	this->dispatchCommentTrigger(machine,
			comment->message(),
			comment->vpos(),
			comment->isYourPost(),
			comment->mail(),
			comment->fromButton(),
			comment->isPremium(),
			comment->color(),
			comment->size(),
			comment->no());
}
void System::dispatchCommentTrigger(machine::Machine& machine, const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
{
	machine.getTopLevel()->setChat(message, vpos, isYourPost, mail, fromButton, isPremium, color, size, no);
	nekomata::TimeLine<EventEntry>::Iterator it = ctrigLine.begin();
	nekomata::TimeLine<EventEntry>::Iterator end = ctrigLine.end();
	const int _color = nextColor();
	log.d(TAG, 0, "Dispathing comment trigger for \"%s\"", message.c_str());
	for(;it != end;){
		std::tr1::shared_ptr<EventEntry> evt = it->getData();
		if(evt->from() <= vpos && evt->to() >= vpos && evt->color() != _color){
			evt->color(_color);
			machine.eval(evt->then());
			it = ctrigLine.begin();
			end = ctrigLine.end();
		}else{
			++it;
		}
	}
}

}}
