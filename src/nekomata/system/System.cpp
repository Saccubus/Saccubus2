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

#include <tr1/memory>
#include <cmath>
#include <nekomata/logging/Logging.h>
#include <nekomata/system/System.h>
#include <algorithm>
#include "../tree/Node.h"
#include "../machine/Machine.h"
#include "../object/Object.h"
#include "../object/SystemObject.h"
#include "../object/Heap.h"

namespace nekomata{
namespace system {

using namespace std::tr1;

static const std::string TAG("System");

System::EventEntry::EventEntry(float const from, float const to, util::Handler<object::LazyEvalObject> obj)
:_from(from),_to(to), _obj(obj) {

}

System::EventEntry::~EventEntry()
{
}
void System::EventEntry::eval(){
	if(_obj->has("then")){
		_obj->forceEval("then");
	}else{
		_obj->forceEval(0);
	}
}

const tree::Location* System::EventEntry::location()
{
	return &_obj->getRawNode()->location();
}
System::System(logging::Logger& log)
:log(log)
,_currentTime(0)
{
}

template <typename T, typename C>
void deleteSystemItems(std::set<T*, C>& map)
{
	typename std::set<T*>::iterator end = map.end();
	for(typename std::set<T*>::iterator it=map.begin();it != end; ++it){
		delete *it;
	}
}

System::~System() {
	deleteSystemItems<Drawable>(drawableList);
	deleteSystemItems<Replace>(replaceList);
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
void System::commentTrigger(float const timer, util::Handler<object::LazyEvalObject> obj)
{
	const tree::Node* node = obj->getRawNode();
	log.v(TAG, 0,
			"commentTrigger(timer: %f, node: (%d, %d in %s), total: %d)",
			timer, node->location().getLineNo(), node->location().getColNo(), node->location().getFilename().c_str(),
			this->ctrigLine.size()
			);
	std::tr1::shared_ptr<EventEntry> evt(new EventEntry(currentTime(), currentTime()+timer, obj));
	this->ctrigLine.insert(std::pair<float, std::tr1::shared_ptr<EventEntry> >(currentTime(), evt));
}
void System::timer(float const timer, util::Handler<object::LazyEvalObject> obj)
{
	const tree::Node* node = obj->getRawNode();
	log.v(TAG, 0,
			"timer(timer: %f+%f=%f, node: (%d, %d in %s), total: %d)",
			currentTime(), timer, currentTime()+timer,
			node->location().getLineNo(), node->location().getColNo(), node->location().getFilename().c_str(),
			this->timerLine.size()+1
			);
	std::tr1::shared_ptr<EventEntry> evt(new EventEntry(currentTime()+timer, currentTime()+timer, obj));
	this->timerLine.insert(std::pair<float, std::tr1::shared_ptr<EventEntry> >(currentTime()+timer, evt));
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
util::Handler<SumResult> System::showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, const std::vector<util::Handler<Sum> >& sum)
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
void System::addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden)
{
	log.v(TAG, 0,
			"addButton(message: %s, mail: %s, vpos: %f, commes: %s, commail: %s, comvisible: %d, limit: %d, hidden:%d)",
			message.c_str(), mail.c_str(), vpos, commes.c_str(), commail.c_str(), comvisible, limit, hidden
			);
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

std::string System::inspect()
{
	return "<<<System>>>";
}

void System::onChanged()
{
	log.v(TAG, 0, "System property changed: %s", inspect().c_str());
}

void System::seek(machine::Machine& machine, const double from, const double to)
{
	if(currentTime() != from){
		log.e(TAG, 0, "[BUG] FIXME: time was not synchronized correctly %f != %f.", currentTime(), from);
	}
	log.t(TAG, 0, "Running: <%f -> %f>", from, to);
	std::deque<std::tr1::shared_ptr<const nekomata::system::Message> >::iterator it = messageQueue.begin();
	for(; it != messageQueue.end() && (*it)->vpos() < to; ++it){
		std::tr1::shared_ptr<const nekomata::system::Message> msg = *it;
		dispatchTimer(machine, currentTime());
		currentTime(msg->vpos());
		switch(msg->type)
		{
		case Message::COMMENT:
		{
			std::tr1::shared_ptr<const Comment> com = std::tr1::dynamic_pointer_cast<const Comment>(msg);
			dispatchCommentTrigger(machine, com);
		}
			break;
		case Message::SCRIPT:
		{
			std::tr1::shared_ptr<const Script> script = std::tr1::dynamic_pointer_cast<const Script>(msg);
			machine.eval(script->node().get());
		}
			break;
		default:
			log.e(TAG, 0, "[BUG] Unknwon message type received.");
			break;
		}
	}
	this->messageQueue.erase(messageQueue.begin(), it);
	currentTime(to);
	dispatchTimer(machine, currentTime());
}

void System::queueMessage(std::tr1::shared_ptr<const Message> message)
{
	std::deque<std::tr1::shared_ptr<const nekomata::system::Message> >::iterator it = std::upper_bound(this->messageQueue.begin(), this->messageQueue.end(), message, Message::ComparatorByVpos());
	this->messageQueue.insert(it, message);
}

void System::dispatchTimer(machine::Machine& machine, const double to)
{
	std::multimap<float, std::tr1::shared_ptr<EventEntry> >::iterator it = timerLine.begin();
	std::multimap<float, std::tr1::shared_ptr<EventEntry> >::iterator end = timerLine.end();
	while(it != end){
		if(to < it->first) break;
		const std::tr1::shared_ptr<EventEntry> nextTimer = it->second;
		currentTime(it->first);
		log.v(TAG, nextTimer->location(), "Current: %f Dispathing timer at: %f left:%d", currentTime(), it->first, timerLine.size());
		nextTimer->eval();
		timerLine.erase(it);
		it=timerLine.begin();
		end = timerLine.end();
	}
	currentTime(to);
}

void System::dispatchCommentTrigger(machine::Machine& machine, std::tr1::shared_ptr<const Comment> comment)
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
	for(std::multimap<float, std::tr1::shared_ptr<EventEntry> >::const_iterator it = ctrigLine.begin();it != ctrigLine.end();++it){
		const std::tr1::shared_ptr<EventEntry> trigger = it->second;
		log.v(TAG, trigger->location(), "Dispathing comment trigger for \"%s\"", message.c_str());
		if(trigger->from() <= vpos && vpos < trigger->to()){
			trigger->eval();
			it=ctrigLine.begin();
			while(it!=ctrigLine.end() && it->second != trigger){
				++it;
			}
		}
	}
}

void System::fetchDrawables(std::vector<Drawable*>& lst)
{
	lst.clear();
	std::copy( drawableList.begin(), drawableList.end(), std::back_inserter(lst));
	std::sort(lst.begin(), lst.end(), Drawable::ComparatorByZ());
}

#define DRAWABLE_REGIST_TEMPLATE(clazz, name) \
void System::regist(clazz* const name)\
{\
	const bool inserted = this->drawableList.insert(name).second;\
	if(!inserted){\
		log.e(TAG, 0, "[BUG] registed duplicated %s!: %s", #clazz, name->inspect().c_str());\
	}\
}\
void System::unregist(clazz* const name)\
{\
	const size_t deleted = this->drawableList.erase(name);\
	if(deleted <= 0){\
		log.e(TAG, 0, "[BUG] unregisted duplicated %s!: %s", #clazz, name->inspect().c_str());\
	}\
	delete name;\
}

DRAWABLE_REGIST_TEMPLATE(Shape, shape)
DRAWABLE_REGIST_TEMPLATE(Label, label)
DRAWABLE_REGIST_TEMPLATE(Sum, sum)
DRAWABLE_REGIST_TEMPLATE(SumResult, sumResult)

#define REGIST_TEMPLATE(clazz, name) \
void System::regist(clazz* const name)\
{\
	const bool inserted = this->name##List.insert(name).second;\
	if(!inserted){\
		log.e(TAG, 0, "[BUG] registed duplicated %s!: %s", #clazz, name->inspect().c_str());\
	}\
}\
void System::unregist(clazz* const name)\
{\
	const size_t deleted = this->name##List.erase(name);\
	if(deleted <= 0){\
		log.e(TAG, 0, "[BUG] unregisted duplicated %s!: %s", #clazz, name->inspect().c_str());\
	}\
	delete name;\
}
REGIST_TEMPLATE(Replace, replace)

#undef DRAWABLE_REGIST_TEMPLATE
#undef REGIST_TEMPLATE

}}
