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

namespace nekomata{
namespace system {

#include "../classdefs.h"

#define DEC_ADAPTER_ACCESSOR(name, type)\
private:\
	type name##_;\
public:\
	virtual type name(){return name##_;}; \
	virtual void name(const type& name##__){name##_=name##__;};

#define SET_PARAM(name) this->name(name)

class Shape
{
public:
	explicit Shape(){};
	virtual ~Shape(){};
public:
	virtual void load(double x, double y, double z, std::string shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover)
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
	DEC_ADAPTER_ACCESSOR(x, double);
	DEC_ADAPTER_ACCESSOR(y, double);
	DEC_ADAPTER_ACCESSOR(z, double);
	DEC_ADAPTER_ACCESSOR(shape, std::string);
	DEC_ADAPTER_ACCESSOR(width, double);
	DEC_ADAPTER_ACCESSOR(height, double);
	DEC_ADAPTER_ACCESSOR(color,unsigned int);
	DEC_ADAPTER_ACCESSOR(visible, bool);
	DEC_ADAPTER_ACCESSOR(pos, std::string);
	DEC_ADAPTER_ACCESSOR(mask, bool);
	DEC_ADAPTER_ACCESSOR(commentmask, bool);
	DEC_ADAPTER_ACCESSOR(alpha, double);
	DEC_ADAPTER_ACCESSOR(rotation, double);
	DEC_ADAPTER_ACCESSOR(mover, std::string);
};

class Sum
{
public:
	explicit Sum(){};
	virtual ~Sum(){};
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
	DEC_ADAPTER_ACCESSOR(x, double);
	DEC_ADAPTER_ACCESSOR(y, double);
	DEC_ADAPTER_ACCESSOR(size, double);
	DEC_ADAPTER_ACCESSOR(color,unsigned int);
	DEC_ADAPTER_ACCESSOR(visible, bool);
	DEC_ADAPTER_ACCESSOR(enabled, bool);
	DEC_ADAPTER_ACCESSOR(pos, std::string);
	DEC_ADAPTER_ACCESSOR(asc, bool);
	DEC_ADAPTER_ACCESSOR(unit, std::string);
	DEC_ADAPTER_ACCESSOR(buttononly, bool);
	DEC_ADAPTER_ACCESSOR(words, std::vector<std::string>);
	DEC_ADAPTER_ACCESSOR(partial, bool);
};
class SumResult
{
public:
	explicit SumResult(){};
	virtual ~SumResult(){};
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
	DEC_ADAPTER_ACCESSOR(x, double);
	DEC_ADAPTER_ACCESSOR(y, double);
	DEC_ADAPTER_ACCESSOR(color,unsigned int);
	DEC_ADAPTER_ACCESSOR(visible, bool);
	DEC_ADAPTER_ACCESSOR(pos, std::string);
	DEC_ADAPTER_ACCESSOR(unit, std::string);
	DEC_ADAPTER_ACCESSOR(asc, bool);
	DEC_ADAPTER_ACCESSOR(sum, std::vector<std::tr1::shared_ptr<Sum> >);
};
class Chat
{
public:
	explicit Chat(){};
	virtual ~Chat(){};
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
	DEC_ADAPTER_ACCESSOR(text, std::string);
	DEC_ADAPTER_ACCESSOR(x, double);
	DEC_ADAPTER_ACCESSOR(y, double);
	DEC_ADAPTER_ACCESSOR(z, double);
	DEC_ADAPTER_ACCESSOR(size, double);
	DEC_ADAPTER_ACCESSOR(pos, std::string);
	DEC_ADAPTER_ACCESSOR(color, unsigned int);
	DEC_ADAPTER_ACCESSOR(bold, bool);
	DEC_ADAPTER_ACCESSOR(visible, bool);
	DEC_ADAPTER_ACCESSOR(filter, std::string);
	DEC_ADAPTER_ACCESSOR(alpha, double);
	DEC_ADAPTER_ACCESSOR(mover, std::string);
};

class Button
{
public:
	explicit Button(){};
	virtual ~Button(){};
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
	DEC_ADAPTER_ACCESSOR(message, std::string);
	DEC_ADAPTER_ACCESSOR(mail, std::string);
	DEC_ADAPTER_ACCESSOR(vpos, double);
	DEC_ADAPTER_ACCESSOR(commes, std::string);
	DEC_ADAPTER_ACCESSOR(commail, std::string);
	DEC_ADAPTER_ACCESSOR(comvisible, bool);
	DEC_ADAPTER_ACCESSOR(limit, int);
	DEC_ADAPTER_ACCESSOR(hidden, bool);
};

class Replace
{
public:
	enum{
		SAME_COLOR=0xffffffff
	};
	explicit Replace(){};
	virtual ~Replace(){};
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
	DEC_ADAPTER_ACCESSOR(src, std::string);
	DEC_ADAPTER_ACCESSOR(dst, std::string);
	DEC_ADAPTER_ACCESSOR(enabled, bool);
	DEC_ADAPTER_ACCESSOR(target, std::string);
	DEC_ADAPTER_ACCESSOR(fill, bool);
	DEC_ADAPTER_ACCESSOR(partial, bool);
	DEC_ADAPTER_ACCESSOR(color, unsigned int);
	DEC_ADAPTER_ACCESSOR(size, std::string);
	DEC_ADAPTER_ACCESSOR(pos, std::string);
};

class System
{
public:
	explicit System();
	virtual ~System();

	virtual std::tr1::shared_ptr<Shape> drawShape(double x, double y, double z, std::string shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
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
	DEC_ADAPTER_ACCESSOR(commentColor, unsigned int);
	DEC_ADAPTER_ACCESSOR(commentPlace, std::string);
	DEC_ADAPTER_ACCESSOR(commentSize, std::string);
	DEC_ADAPTER_ACCESSOR(commentInvisible, bool);
	DEC_ADAPTER_ACCESSOR(commentReverse, bool);
	DEC_ADAPTER_ACCESSOR(defaultSage, bool);
	DEC_ADAPTER_ACCESSOR(postDisabled, bool);
	DEC_ADAPTER_ACCESSOR(seekDisabled, bool);
	DEC_ADAPTER_ACCESSOR(isLoaded, bool);
	DEC_ADAPTER_ACCESSOR(isWide, bool);
	DEC_ADAPTER_ACCESSOR(lastVideo, std::string);
};

#undef DEC_ADAPTER_ACCESSOR
#undef SET_PARAM

}
}
#endif /* SYSTEM_H_ */
