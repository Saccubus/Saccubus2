/*
 * System.h
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <tr1/memory>

namespace nekomata{
namespace system {

#include "../classdefs.h"

#define DEC_ADAPTER_ACCESSOR(name, type)\
private:\
	type name##_;\
public:\
	virtual type name(){return name##_;}; \
	virtual void name(const type& name##__){name##_=name##__;};

class Shape
{
public:
	explicit Shape(){};
	virtual ~Shape(){};
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
};
class SumResult
{
public:
	explicit SumResult(){};
	virtual ~SumResult(){};
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
	explicit Replace(){};
	virtual ~Replace(){};
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

	virtual std::tr1::shared_ptr<Chat> drawText(const std::string& text, double x, double y, double z, double size,const std::string& pos,unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover) = 0;
	virtual std::tr1::shared_ptr<Shape> drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover) = 0;
	virtual std::tr1::shared_ptr<Sum> sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, std::string& unit,bool buttononly, std::vector<std::string>& words) = 0;
	virtual std::tr1::shared_ptr<SumResult> showResult(double x, double y, unsigned int color, bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<Sum*>& sum) = 0;
	virtual std::tr1::shared_ptr<Replace> replace(const std::string& src, const std::string& dest, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, double size, const std::string& pos) = 0;
	virtual void seek(double vpos, const std::string& msg) = 0;
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow) = 0;
	virtual double screenWidth() = 0;
	virtual double screenHeight() = 0;
	virtual Button* addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden) = 0;
	virtual double playStartTime() = 0;
	virtual void BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume) = 0;
	virtual void playBGM(int id) = 0;
	virtual void stopBGM(int id) = 0;
	virtual void addAtPausePoint(double vpos, double wait) = 0;
	virtual void addPostRoute(const std::string& match, const std::string& id, const std::string& button) = 0;
	virtual void CM(const std::string& id, double time, bool pause, const std::string& link, double volume) = 0;
	virtual void playCM(int id) = 0;
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

}
}
#endif /* SYSTEM_H_ */
