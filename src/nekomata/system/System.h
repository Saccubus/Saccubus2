/*
 * System.h
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <string>
#include <vector>
#include <map>
#include "../classdefs.h"
#include "../TimeLine.h"
#include "../util/Handler.h"

namespace nekomata{
namespace system {

#define DEF_ADAPTER_ACCESSOR(name, type)\
private:\
	type name##_;\
public:\
	virtual type name() const{return name##_;} \
	virtual void name(const type& name##__){\
		name##_=name##__;\
	}
#define SET_PARAM(name) this->name(_##name)
#define SET_DEFAULT(name, val) name##_(val)

class SystemItem
{
private:
	int nativeRef;
protected:
	System& system;
public:
	explicit SystemItem(System& system):system(system){};
	virtual ~SystemItem(){};
public:
	int getNativeRef(){return nativeRef;}
	virtual void incNativeRef(){};
	virtual void decNativeRef(){};
};

class Shape : public SystemItem
{
public:
	virtual void load(double _x, double _y, double _z, const std::string& _shape, double _width, double _height, unsigned int _color, bool _visible, const std::string& _pos, bool _mask, bool _commentmask, double _alpha, double _rotation, const std::string& _mover)
	{
		SET_PARAM(x);
		SET_PARAM(y);
		SET_PARAM(z);
		SET_PARAM(shape);
		SET_PARAM(width);
		SET_PARAM(height);
		SET_PARAM(color);
		SET_PARAM(visible);
		SET_PARAM(pos);
		SET_PARAM(mask);
		SET_PARAM(commentmask);
		SET_PARAM(alpha);
		SET_PARAM(rotation);
		SET_PARAM(mover);
	}
public:
	DEF_ADAPTER_ACCESSOR(x, double);
	DEF_ADAPTER_ACCESSOR(y, double);
	DEF_ADAPTER_ACCESSOR(z, double);
	DEF_ADAPTER_ACCESSOR(shape, std::string);
	DEF_ADAPTER_ACCESSOR(width, double);
	DEF_ADAPTER_ACCESSOR(height, double);
	DEF_ADAPTER_ACCESSOR(color,unsigned int);
	DEF_ADAPTER_ACCESSOR(visible, bool);
	DEF_ADAPTER_ACCESSOR(pos, std::string);
	DEF_ADAPTER_ACCESSOR(mask, bool);
	DEF_ADAPTER_ACCESSOR(commentmask, bool);
	DEF_ADAPTER_ACCESSOR(alpha, double);
	DEF_ADAPTER_ACCESSOR(rotation, double);
	DEF_ADAPTER_ACCESSOR(mover, std::string);
public:
	explicit Shape(System& system)
	:SystemItem(system), SET_DEFAULT(visible, false){};
	virtual ~Shape(){};
};

class Sum : public SystemItem
{
public:
	virtual void load(double _x, double _y, double _size, unsigned int _color,bool _visible, bool _enabled, const std::string& _pos, bool _asc, const std::string& _unit, bool _buttononly, const std::vector<std::string>& _words, bool _partial)
	{
		SET_PARAM(x);
		SET_PARAM(y);
		SET_PARAM(size);
		SET_PARAM(color);
		SET_PARAM(visible);
		SET_PARAM(enabled);
		SET_PARAM(pos);
		SET_PARAM(asc);
		SET_PARAM(unit);
		SET_PARAM(buttononly);
		SET_PARAM(words);
		SET_PARAM(partial);
	}
public:
	DEF_ADAPTER_ACCESSOR(x, double);
	DEF_ADAPTER_ACCESSOR(y, double);
	DEF_ADAPTER_ACCESSOR(size, double);
	DEF_ADAPTER_ACCESSOR(color,unsigned int);
	DEF_ADAPTER_ACCESSOR(visible, bool);
	DEF_ADAPTER_ACCESSOR(enabled, bool);
	DEF_ADAPTER_ACCESSOR(pos, std::string);
	DEF_ADAPTER_ACCESSOR(asc, bool);
	DEF_ADAPTER_ACCESSOR(unit, std::string);
	DEF_ADAPTER_ACCESSOR(buttononly, bool);
	DEF_ADAPTER_ACCESSOR(words, std::vector<std::string>);
	DEF_ADAPTER_ACCESSOR(partial, bool);
public:
	explicit Sum(System& system)
	:SystemItem(system), SET_DEFAULT(visible, false){};
	virtual ~Sum(){};
};
class SumResult : public SystemItem
{
public:
	virtual void load(double _x, double _y, unsigned int _color,bool _visible, const std::string& _pos, const std::string& _unit, bool _asc, std::vector<util::Handler<Sum> > _sum)
	{
		SET_PARAM(x);
		SET_PARAM(y);
		SET_PARAM(color);
		SET_PARAM(visible);
		SET_PARAM(pos);
		SET_PARAM(unit);
		SET_PARAM(asc);
		SET_PARAM(sum);
	}
public:
	DEF_ADAPTER_ACCESSOR(x, double);
	DEF_ADAPTER_ACCESSOR(y, double);
	DEF_ADAPTER_ACCESSOR(color,unsigned int);
	DEF_ADAPTER_ACCESSOR(visible, bool);
	DEF_ADAPTER_ACCESSOR(pos, std::string);
	DEF_ADAPTER_ACCESSOR(unit, std::string);
	DEF_ADAPTER_ACCESSOR(asc, bool);
	DEF_ADAPTER_ACCESSOR(sum, std::vector<util::Handler<Sum> >);
public:
	explicit SumResult(System& system)
	:SystemItem(system), SET_DEFAULT(visible, false){};
	virtual ~SumResult(){};
};
class Label : public SystemItem
{
public:
	virtual void load(const std::string& _text, double _x, double _y, double _z, double _size, const std::string& _pos, unsigned int _color, bool _bold, bool _visible, const std::string& _filter, double _alpha, const std::string& _mover)
	{
		SET_PARAM(text);
		SET_PARAM(x);
		SET_PARAM(y);
		SET_PARAM(z);
		SET_PARAM(size);
		SET_PARAM(pos);
		SET_PARAM(color);
		SET_PARAM(bold);
		SET_PARAM(visible);
		SET_PARAM(filter);
		SET_PARAM(alpha);
		SET_PARAM(mover);
	}
public:
	DEF_ADAPTER_ACCESSOR(text, std::string);
	DEF_ADAPTER_ACCESSOR(x, double);
	DEF_ADAPTER_ACCESSOR(y, double);
	DEF_ADAPTER_ACCESSOR(z, double);
	DEF_ADAPTER_ACCESSOR(size, double);
	DEF_ADAPTER_ACCESSOR(pos, std::string);
	DEF_ADAPTER_ACCESSOR(color, unsigned int);
	DEF_ADAPTER_ACCESSOR(bold, bool);
	DEF_ADAPTER_ACCESSOR(visible, bool);
	DEF_ADAPTER_ACCESSOR(filter, std::string);
	DEF_ADAPTER_ACCESSOR(alpha, double);
	DEF_ADAPTER_ACCESSOR(mover, std::string);
public:
	explicit Label(System& system):
	SystemItem(system), SET_DEFAULT(visible, false){};
	virtual ~Label(){};
};

class Button : public SystemItem
{
public:
	virtual void load(const std::string& _message, const std::string& _mail, double _vpos, const std::string& _commes, const std::string& _commail, bool _comvisible, int _limit, bool _hidden)
	{
		SET_PARAM(message);
		SET_PARAM(mail);
		SET_PARAM(vpos);
		SET_PARAM(commes);
		SET_PARAM(commail);
		SET_PARAM(comvisible);
		SET_PARAM(limit);
		SET_PARAM(hidden);
	}
public:
	DEF_ADAPTER_ACCESSOR(message, std::string);
	DEF_ADAPTER_ACCESSOR(mail, std::string);
	DEF_ADAPTER_ACCESSOR(vpos, double);
	DEF_ADAPTER_ACCESSOR(commes, std::string);
	DEF_ADAPTER_ACCESSOR(commail, std::string);
	DEF_ADAPTER_ACCESSOR(comvisible, bool);
	DEF_ADAPTER_ACCESSOR(limit, int);
	DEF_ADAPTER_ACCESSOR(hidden, bool);
public:
	explicit Button(System& system)
	:SystemItem(system), SET_DEFAULT(hidden, true){};
	virtual ~Button(){};
};

class Replace : public SystemItem
{
public:
	virtual void load(const std::string& _src, const std::string& _dst, bool _enabled, const std::string& _target, bool _fill, bool _partial, unsigned int _color, const std::string& _size, const std::string& _pos)
	{
		SET_PARAM(src);
		SET_PARAM(dst);
		SET_PARAM(enabled);
		SET_PARAM(target);
		SET_PARAM(fill);
		SET_PARAM(partial);
		SET_PARAM(color);
		SET_PARAM(size);
		SET_PARAM(pos);
	}
public:
	DEF_ADAPTER_ACCESSOR(src, std::string);
	DEF_ADAPTER_ACCESSOR(dst, std::string);
	DEF_ADAPTER_ACCESSOR(enabled, bool);
	DEF_ADAPTER_ACCESSOR(target, std::string);
	DEF_ADAPTER_ACCESSOR(fill, bool);
	DEF_ADAPTER_ACCESSOR(partial, bool);
	DEF_ADAPTER_ACCESSOR(color, unsigned int);
	DEF_ADAPTER_ACCESSOR(size, std::string);
	DEF_ADAPTER_ACCESSOR(pos, std::string);
public:
	enum{
		SAME_COLOR=0xffffffff
	};
	explicit Replace(System& system)
	:SystemItem(system), SET_DEFAULT(enabled, false){};
	virtual ~Replace(){};
};

//---------------------------------------------------------------------------------------------------------------------

class Comment
{
private:
	const bool _isValid;
	int _color;
public:
	DEF_ADAPTER_ACCESSOR(message, std::string);
	DEF_ADAPTER_ACCESSOR(vpos, double);
	DEF_ADAPTER_ACCESSOR(isYourPost, bool);
	DEF_ADAPTER_ACCESSOR(mail, std::string);
	DEF_ADAPTER_ACCESSOR(fromButton, bool);
	DEF_ADAPTER_ACCESSOR(isPremium, bool);
	DEF_ADAPTER_ACCESSOR(color, unsigned int);
	DEF_ADAPTER_ACCESSOR(size, double);
	DEF_ADAPTER_ACCESSOR(no, unsigned int);
public:
	explicit Comment(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
	:_isValid(true),
	_color(0),
	SET_DEFAULT(message, message),
	SET_DEFAULT(vpos, vpos),
	SET_DEFAULT(isYourPost, isYourPost),
	SET_DEFAULT(mail, mail),
	SET_DEFAULT(fromButton, fromButton),
	SET_DEFAULT(isPremium, isPremium),
	SET_DEFAULT(color, color),
	SET_DEFAULT(size, size),
	SET_DEFAULT(no, no)
	{};
	explicit Comment()
	:_isValid(false),
	_color(0),
	SET_DEFAULT(message, ""),
	SET_DEFAULT(vpos, NAN),
	SET_DEFAULT(isYourPost, false),
	SET_DEFAULT(mail, ""),
	SET_DEFAULT(fromButton, false),
	SET_DEFAULT(isPremium, false),
	SET_DEFAULT(color, false),
	SET_DEFAULT(size, false),
	SET_DEFAULT(no, false)
	{};
	virtual ~Comment(){};
public:
	bool isValid(){return _isValid;};
public:
	int objColor() const{return _color;};
	void objColor(int color) {_color = color;};
};

//----------------------------------------------------------------------------------------------------------------------

class System
{
private:
	class EventEntry{
	public:
		EventEntry(float const from, float const to, const tree::Node* then): _color(0), _from(from), _to(to), _then(then){};
		virtual ~EventEntry(){};
	private:
		int _color;
		const float _from;
		const float _to;
		const tree::Node* _then;
	public:
		int color(){return _color;};
		void color(int color){_color = color;};
		float from(){return _from;}
		float to(){return _to;}
		const tree::Node* then(){return _then;}
	};
	float _currentTime;
	int color;
protected:
	float currentTime(){return _currentTime;}
	void currentTime(float time){_currentTime=time;}
protected:
	int nextColor(){return ++color;}
private:
	std::map<std::string, double> markerMap;
	std::vector<Shape*> shapeList;
	std::vector<Label*> labelList;
	std::vector<Sum*> sumList;
	std::vector<SumResult*> sumResultList;
	std::vector<Replace*> replaceList;
	std::vector<Button*> buttonList;
	nekomata::TimeLine<EventEntry> timerLine;
	nekomata::TimeLine<EventEntry> ctrigLine;
	logging::Logger& log;
public:
	explicit System(logging::Logger& log);
	virtual ~System();

	virtual util::Handler<Shape> drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
	virtual util::Handler<Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
	virtual void commentTrigger(float const timer, const tree::Node* then);
	virtual void timer(float const timer, const tree::Node* then);
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow);
	virtual void jumpCancel();
	virtual void seek(double vpos, const std::string& msg);
	virtual void addMarker(const std::string& name, double vpos);
	virtual double getMarker(const std::string& name);
	virtual util::Handler<Sum> sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial);
	virtual util::Handler<SumResult> showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<util::Handler<Sum> > sum);
	virtual util::Handler<Replace> replace(const std::string& src, const std::string& dst, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos);
	virtual double screenWidth();
	virtual double screenHeight();
	virtual util::Handler<Button> addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden);
	virtual double playStartTime();
	virtual void BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume);
	virtual void playBGM(int id);
	virtual void stopBGM(int id);
	virtual void addAtPausePoint(double vpos, double wait);
	virtual void addPostRoute(const std::string& match, const std::string& id, const std::string& button);
	virtual void CM(const std::string& id, double time, bool pause, const std::string& link, double volume);
	virtual void playCM(int id);
private:
	void dispatchCommentTrigger(machine::Machine& machine, const Comment* comment);
	void dispatchCommentTrigger(machine::Machine& machine, const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no);
	const TimePoint<System::EventEntry>* findFirstTimer(const int color, const double from, const double to);
public:
	void seek(machine::Machine& machine, const double from, const double to);
public:
	virtual Comment findFirstComment(const int objColor, const double from, const double to){return Comment();};
	virtual nekomata::TimeLine<system::Comment>* getCommentTimeLine(){return 0;};
public:
	DEF_ADAPTER_ACCESSOR(commentColor, unsigned int);
	DEF_ADAPTER_ACCESSOR(commentPlace, std::string);
	DEF_ADAPTER_ACCESSOR(commentSize, std::string);
	DEF_ADAPTER_ACCESSOR(commentInvisible, bool);
	DEF_ADAPTER_ACCESSOR(commentReverse, bool);
	DEF_ADAPTER_ACCESSOR(defaultSage, bool);
	DEF_ADAPTER_ACCESSOR(postDisabled, bool);
	DEF_ADAPTER_ACCESSOR(seekDisabled, bool);
	DEF_ADAPTER_ACCESSOR(isLoaded, bool);
	DEF_ADAPTER_ACCESSOR(isWide, bool);
	DEF_ADAPTER_ACCESSOR(lastVideo, std::string);
};


#undef DEF_ADAPTER_ACCESSOR
#undef SET_PARAM
#undef SET_DEFAULT

}}
#endif /* SYSTEM_H_ */
