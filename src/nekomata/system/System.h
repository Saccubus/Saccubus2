/*
 * System.h
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <tr1/memory>
#include <string>
#include <vector>
#include <map>
#include "../classdefs.h"

namespace nekomata{
namespace system {

#define DEF_ADAPTER_ACCESSOR(name, type)\
private:\
	type name##_;\
public:\
	virtual type name(){return name##_;} \
	virtual void name(const type& name##__){\
		if(this->name##_ != name##_){\
			name##_=name##__;\
		}\
	}

class System
{
private:
	std::map<std::string, double> markerMap;
protected:
	logging::Logger& log;
public:
	explicit System(logging::Logger& log);
	virtual ~System();

	virtual std::tr1::shared_ptr<Shape> drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
	virtual std::tr1::shared_ptr<Chat> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
	virtual void commentTrigger(float const timer, const tree::Node* then);
	virtual void timer(float const timer, const tree::Node* then);
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow);
	virtual void jumpCancel();
	virtual void seek(double vpos, const std::string& msg);
	virtual void addMarker(const std::string& name, double vpos);
	virtual double getMarker(const std::string& name);
	virtual std::tr1::shared_ptr<Sum> sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial);
	virtual std::tr1::shared_ptr<SumResult> showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<std::tr1::shared_ptr<Sum> > sum);
	virtual std::tr1::shared_ptr<Replace> replace(const std::string& src, const std::string& dst, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos);
	virtual double screenWidth();
	virtual double screenHeight();
	virtual std::tr1::shared_ptr<Button> addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden);
	virtual double playStartTime();
	virtual void BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume);
	virtual void playBGM(int id);
	virtual void stopBGM(int id);
	virtual void addAtPausePoint(double vpos, double wait);
	virtual void addPostRoute(const std::string& match, const std::string& id, const std::string& button);
	virtual void CM(const std::string& id, double time, bool pause, const std::string& link, double volume);
	virtual void playCM(int id);
//
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
//---------------------------------------------------------------------------------------------------------------------

#define SET_PARAM(name) this->name(name)
#define SET_DEFAULT(name, val) name##_(val)

class SystemItem
{
protected:
	System& system;
public:
	explicit SystemItem(System& system):system(system){};
	virtual ~SystemItem(){};
};

class Shape : public SystemItem
{
public:
	virtual void load(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover)
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
	virtual void load(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial)
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
	virtual void load(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<std::tr1::shared_ptr<Sum> > sum)
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
	DEF_ADAPTER_ACCESSOR(sum, std::vector<std::tr1::shared_ptr<Sum> >);
public:
	explicit SumResult(System& system)
	:SystemItem(system), SET_DEFAULT(visible, false){};
	virtual ~SumResult(){};
};
class Chat : public SystemItem
{
public:
	virtual void load(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover)
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
	explicit Chat(System& system):
	SystemItem(system), SET_DEFAULT(visible, false){};
	virtual ~Chat(){};
};

class Button : public SystemItem
{
public:
	virtual void load(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden)
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
	virtual void load(const std::string& src, const std::string& dst, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos)
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

#undef DEF_ADAPTER_ACCESSOR
#undef SET_PARAM
#undef SET_DEFAULT

}}
#endif /* SYSTEM_H_ */
