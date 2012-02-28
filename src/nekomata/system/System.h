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

#define DEF_DEFAULT(name, value) name##_(value)

class Shape
{
public:
	explicit Shape():
	DEF_DEFAULT(x, 0),
	DEF_DEFAULT(y, 0),
	DEF_DEFAULT(z, 0),
	DEF_DEFAULT(shape, "circle"),
	DEF_DEFAULT(width, 30),
	DEF_DEFAULT(height, 30),
	DEF_DEFAULT(color, 16777215),
	DEF_DEFAULT(visible, true),
	DEF_DEFAULT(pos, "naka"),
	DEF_DEFAULT(mask, false),
	DEF_DEFAULT(commentmask, false),
	DEF_DEFAULT(alpha, 0),
	DEF_DEFAULT(rotation, 0),
	DEF_DEFAULT(mover, "")
	{};
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
	explicit Sum():
	DEF_DEFAULT(x, 0),
	DEF_DEFAULT(y, 0),
	DEF_DEFAULT(size, 30),
	DEF_DEFAULT(color,16777215),
	DEF_DEFAULT(visible, true),
	DEF_DEFAULT(enabled, true),
	DEF_DEFAULT(pos, "naka"),
	DEF_DEFAULT(asc, false),
	DEF_DEFAULT(unit, "人"),
	DEF_DEFAULT(buttononly, false),
	DEF_DEFAULT(words, std::vector<std::string>()),
	DEF_DEFAULT(partial, false)
	{};
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
	DEC_ADAPTER_ACCESSOR(partial, bool);
};
class SumResult
{
public:
	explicit SumResult():
	DEF_DEFAULT(x, 0),
	DEF_DEFAULT(y, 0),
	DEF_DEFAULT(color,16777215),
	DEF_DEFAULT(visible, true),
	DEF_DEFAULT(pos, "naka"),
	DEF_DEFAULT(unit, "人"),
	DEF_DEFAULT(asc, false),
	DEF_DEFAULT(sum, std::vector<std::tr1::shared_ptr<Sum> >())
	{};
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
	explicit Chat():
	DEF_DEFAULT(text, std::string),
	DEF_DEFAULT(x, 0),
	DEF_DEFAULT(y, 0),
	DEF_DEFAULT(z, 0),
	DEF_DEFAULT(size, 14),
	DEF_DEFAULT(pos, "naka"),
	DEF_DEFAULT(color, 0),
	DEF_DEFAULT(bold, false),
	DEF_DEFAULT(visible, true),
	DEF_DEFAULT(filter, ""),
	DEF_DEFAULT(alpha, 0),
	DEF_DEFAULT(mover, "")
	{};
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
	explicit Button():
	DEF_DEFAULT(message, ""),
	DEF_DEFAULT(mail, ""),
	DEF_DEFAULT(vpos, 0), //FIXME: Wikiに書いてない
	DEF_DEFAULT(commes, ""), //FIXME: Wikiに書いてない
	DEF_DEFAULT(commail, ""),
	DEF_DEFAULT(comvisible, true),
	DEF_DEFAULT(limit, 1),
	DEF_DEFAULT(hidden, false)
	{};
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
	enum{
		SAME_COLOR=0xffffffff
	};
public:
	explicit Replace():
	DEF_DEFAULT(src, ""),
	DEF_DEFAULT(dst, ""), //TODO: SRCと同じ文字
	DEF_DEFAULT(enabled, true),
	DEF_DEFAULT(target, ""),
	DEF_DEFAULT(fill, false),
	DEF_DEFAULT(partial, true),
	DEF_DEFAULT(color, SAME_COLOR), //変更しない
	DEF_DEFAULT(size, ""),
	DEF_DEFAULT(pos, "")
	{};
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

	virtual std::tr1::shared_ptr<Shape> drawShape(std::tr1::shared_ptr<Shape> _shape) = 0;
	virtual std::tr1::shared_ptr<Chat> drawText(std::tr1::shared_ptr<Chat> _chat) = 0;
	virtual void commentTrigger(float const timer, const tree::Node* then) = 0;
	virtual void timer(float const timer, const tree::Node* then) = 0;
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow) = 0;
	virtual void jumpCancel() = 0;
	virtual void seek(double vpos, const std::string& msg) = 0;
	virtual void addMarker(const std::string& name, double vpos) = 0;
	virtual void getMarker(const std::string& name) = 0;
	virtual std::tr1::shared_ptr<Sum> sum(std::tr1::shared_ptr<Sum> _sum) = 0;
	virtual std::tr1::shared_ptr<SumResult> showResult(std::tr1::shared_ptr<SumResult> _sumResult) = 0;
	virtual std::tr1::shared_ptr<Replace> replace(std::tr1::shared_ptr<Replace> _replace) = 0;
	virtual double screenWidth() = 0;
	virtual double screenHeight() = 0;
	virtual std::tr1::shared_ptr<Button> addButton(std::tr1::shared_ptr<Button> _button) = 0;
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
#undef DEF_DEFAULT

}
}
#endif /* SYSTEM_H_ */
