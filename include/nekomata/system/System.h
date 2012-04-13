/*
 * System.h
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <cmath>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <tr1/memory>
#include "../classdefs.h"
#include "../util/Handler.h"

namespace nekomata{
namespace system {

#define DEF_ADAPTER_ACCESSOR(name, type)\
private:\
	type name##_;\
	virtual void ___##name(const type& name##__){\
		this->name##_=name##__;\
	}\
public:\
	virtual type name() const{return name##_;} \
	virtual void name(const type& name##__){\
		if(this->name##_ != name##__){\
			this->___##name(name##__);\
			this->onChanged();\
		}\
	}
#define SET_PARAM(name) this->___##name(_##name)
#define SET_DEFAULT(name, val) name##_(val)

class SystemItem
{
protected:
	System& system;
private:
	int nativeRef;
public:
	explicit SystemItem(System& system):system(system), nativeRef(0){};
	virtual ~SystemItem(){};
protected:
	virtual void onChanged();
	virtual std::string inspect() = 0;
public:
	int getNativeRef(){return nativeRef;}
	virtual void incNativeRef();
	virtual void decNativeRef();
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
	virtual void incNativeRef();
	virtual void decNativeRef();
	virtual std::string inspect();
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
	virtual void incNativeRef();
	virtual void decNativeRef();
	virtual std::string inspect();
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
	virtual void incNativeRef();
	virtual void decNativeRef();
	virtual std::string inspect();
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
	virtual void incNativeRef();
	virtual void decNativeRef();
	virtual std::string inspect();
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
	virtual void incNativeRef();
	virtual void decNativeRef();
	virtual std::string inspect();
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
	virtual void incNativeRef();
	virtual void decNativeRef();
	virtual std::string inspect();
};

//---------------------------------------------------------------------------------------------------------------------

class Comment
{
public:
	enum Type{
		INVALID=0,
		COMMENT=1,
		SCRIPT=2
	};
private:
	const enum Type type;
public:
	const std::string message_;
	std::string message() const{return message_;};

	const double vpos_;
	double vpos() const{return vpos_;};

	const bool isYourPost_;
	bool isYourPost() const{return isYourPost_;};

	const std::string mail_;
	std::string mail() const{return mail_;};

	const bool fromButton_;
	bool fromButton() const{return fromButton_;};

	const bool isPremium_;
	bool isPremium() const{return isPremium_;};

	const unsigned int color_;
	unsigned int color() const{return color_;};

	const double size_;
	double size() const{return size_;};

	const unsigned int no_;
	unsigned int no() const{return no_;};

	std::tr1::shared_ptr<const tree::Node> node_;
	std::tr1::shared_ptr<const tree::Node> node() const{return node_;};
public:
	explicit Comment(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no)
	:type(COMMENT),
	message_(message),
	vpos_(vpos),
	isYourPost_(isYourPost),
	mail_(mail),
	fromButton_(fromButton),
	isPremium_(isPremium),
	color_(color),
	size_(size),
	no_(no),
	node_()
	{};
	explicit Comment(const float vpos, std::tr1::shared_ptr<const tree::Node> node)
	:type(SCRIPT),
	message_(""),
	vpos_(vpos),
	isYourPost_(false),
	mail_(""),
	fromButton_(false),
	isPremium_(false),
	color_(false),
	size_(false),
	no_(false),
	node_(node)
	{};
	explicit Comment()
	:type(INVALID),
	message_(""),
	vpos_(NAN),
	isYourPost_(false),
	mail_(""),
	fromButton_(false),
	isPremium_(false),
	color_(false),
	size_(false),
	no_(false),
	node_()
	{};
	virtual ~Comment(){};
public:
	bool isValid() const{return type != INVALID;};
	bool hasScript() const{return type == SCRIPT;};
	bool isComment() const{return type == COMMENT;};
};

//----------------------------------------------------------------------------------------------------------------------

class System
{
private:
	class EventEntry{
	public:
		EventEntry(float const from, float const to, const tree::Node* then): _from(from), _to(to), _then(then){};
		virtual ~EventEntry(){};
	private:
		const float _from;
		const float _to;
		const tree::Node* _then;
	public:
		float from(){return _from;}
		float to(){return _to;}
		const tree::Node* then(){return _then;}
	};
public:
	logging::Logger& log;
	explicit System(logging::Logger& log);
	virtual ~System();
private:
	float _currentTime;
	std::tr1::shared_ptr<const Comment> currentComment;
public:
	float currentTime(){return _currentTime;}
protected:
	void currentTime(float time){_currentTime=time;}
private:
	void dispatchCommentTrigger(machine::Machine& machine, std::tr1::shared_ptr<const Comment> comment);
	void dispatchCommentTrigger(machine::Machine& machine, const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no);
	void dispatchTimer(machine::Machine& machine, const double from, const double to);
//---------------------------------------------------------------------------------------------------------------------
public: /* スクリプトから参照される */
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
private:
	std::map<std::string, double> markerMap;
	std::set<Shape*> shapeList;
	std::set<Label*> labelList;
	std::set<Sum*> sumList;
	std::set<SumResult*> sumResultList;
	std::set<Replace*> replaceList;
	std::set<Button*> buttonList;
	std::multimap<float, std::tr1::shared_ptr<EventEntry>, std::less<float> > timerLine;
	std::multimap<float, std::tr1::shared_ptr<EventEntry>, std::less<float> > ctrigLine;
public: /* SystemItemからのコールバック関数 */
	void regist(Shape* const shape);
	void unregist(Shape* const shape);

	void regist(Label* const label);
	void unregist(Label* const label);

	void regist(Sum* const sum);
	void unregist(Sum* const sum);

	void regist(SumResult* const sumResult);
	void unregist(SumResult* const sumResult);

	void regist(Replace* const replace);
	void unregist(Replace* const replace);

	void regist(Button* const button);
	void unregist(Button* const button);
public: /* Nekomataから操作される */
	void seek(machine::Machine& machine, const double from, const double to);
public: /* INFO: 各サブシステムで再実装すること。 */
	virtual std::tr1::shared_ptr<const Comment> nextComment() = 0;
protected: /* INFO: 各サブシステムで再実装すること。 */
	virtual std::string inspect();
	void onChanged();
};


#undef DEF_ADAPTER_ACCESSOR
#undef SET_PARAM
#undef SET_DEFAULT

}}
#endif /* SYSTEM_H_ */
