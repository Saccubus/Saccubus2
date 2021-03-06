/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <cmath>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <memory>
#include <deque>
#include <cinamo/Handler.h>
#include "../classdefs.h"

namespace nekomata{
namespace system {
using cinamo::Handler;

#define DEF_ADAPTER_ACCESSOR(rscope, wscope, type, name)\
protected:\
	type name##_;\
rscope:\
	inline type const& name() const{return name##_;}\
wscope:\
	virtual void name(type const& val){\
		if(this->name##_ != val){\
			this->name##_=val;\
			this->onChanged();\
		}\
	}

#define SET_PARAM(name) this->name##_ = name##_;
#define SET_PARAM_CONST(name, val) this->name##_ = val;
#define SET_DEFAULT(name, val) name##_(val)

class SystemItem : public cinamo::HandlerBody<SystemItem>
{
protected:
	System& system;
public:
	explicit SystemItem(System& system):system(system){};
	virtual ~SystemItem() noexcept = default;
	bool onFree() noexcept { return false; };
protected:
	virtual void onChanged();
	virtual std::string inspect() = 0;
};

class Drawable : public SystemItem
{
	DEF_ADAPTER_ACCESSOR(public, public, double, x);
	DEF_ADAPTER_ACCESSOR(public, public, double, y);
	DEF_ADAPTER_ACCESSOR(public, public, double, z);
	DEF_ADAPTER_ACCESSOR(public, public, bool, visible);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, pos);
protected:
	explicit Drawable(System& system)
	:SystemItem(system)
	,SET_DEFAULT(x, 0),SET_DEFAULT(y, 0),SET_DEFAULT(z, 0),SET_DEFAULT(visible, false),SET_DEFAULT(pos, ""){};
public:
	virtual ~Drawable() noexcept = default;
public:
	struct ComparatorByZ{
		bool operator () (Drawable* const a, Drawable* const b);
		bool operator () (Drawable* const a, const double& b);
		bool operator () (const double& a, Drawable* const b);
	};
};

class Shape : public Drawable
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
	DEF_ADAPTER_ACCESSOR(public, public, std::string, shape);
	DEF_ADAPTER_ACCESSOR(public, public, double, width);
	DEF_ADAPTER_ACCESSOR(public, public, double, height);
	DEF_ADAPTER_ACCESSOR(public, public, unsigned int, color);
	DEF_ADAPTER_ACCESSOR(public, public, bool, mask);
	DEF_ADAPTER_ACCESSOR(public, public, bool, commentmask);
	DEF_ADAPTER_ACCESSOR(public, public, double, alpha);
	DEF_ADAPTER_ACCESSOR(public, public, double, rotation);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, mover);
public:
	explicit Shape(System& system)
	:Drawable(system) {};
	virtual ~Shape() noexcept = default;
	void incref(bool opt);
	void decref();
	virtual std::string inspect();
};

class Sum : public Drawable
{
public:
	virtual void load(double _x, double _y, double _size, unsigned int _color,bool _visible, bool _enabled, const std::string& _pos, bool _asc, const std::string& _unit, bool _buttononly, const std::vector<std::string>& _words, bool _partial)
	{
		SET_PARAM(x);
		SET_PARAM(y);
		SET_PARAM_CONST(z, -1);
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
	DEF_ADAPTER_ACCESSOR(public, public, double, size);
	DEF_ADAPTER_ACCESSOR(public, public,unsigned int, color);
	DEF_ADAPTER_ACCESSOR(public, public, bool, enabled);
	DEF_ADAPTER_ACCESSOR(public, public, bool, asc);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, unit);
	DEF_ADAPTER_ACCESSOR(public, public, bool, buttononly);
	DEF_ADAPTER_ACCESSOR(public, public, std::vector<std::string>, words);
	DEF_ADAPTER_ACCESSOR(public, public, bool, partial);
public:
	explicit Sum(System& system)
	:Drawable(system){};
	virtual ~Sum() noexcept = default;
	void incref(bool opt);
	void decref();
	virtual std::string inspect();
};
class SumResult : public Drawable
{
public:
	virtual void load(double _x, double _y, unsigned int _color,bool _visible, const std::string& _pos, const std::string& _unit, bool _asc, std::vector<Handler<Sum> > _sum)
	{
		SET_PARAM(x);
		SET_PARAM(y);
		SET_PARAM_CONST(z, -1);
		SET_PARAM(color);
		SET_PARAM(visible);
		SET_PARAM(pos);
		SET_PARAM(unit);
		SET_PARAM(asc);
		SET_PARAM(sum);
	}
public:
	DEF_ADAPTER_ACCESSOR(public, public,unsigned int, color);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, pos);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, unit);
	DEF_ADAPTER_ACCESSOR(public, public, bool, asc);
	DEF_ADAPTER_ACCESSOR(public, public, std::vector<Handler<Sum> >, sum);
public:
	explicit SumResult(System& system)
	:Drawable(system){
		SET_PARAM_CONST(visible, false);
	};
	virtual ~SumResult() noexcept = default;
	void incref(bool opt);
	void decref();
	virtual std::string inspect();
};
class Label : public Drawable
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
	DEF_ADAPTER_ACCESSOR(public, public, std::string, text);
	DEF_ADAPTER_ACCESSOR(public, public, double, size);
	DEF_ADAPTER_ACCESSOR(public, public, unsigned int, color);
	DEF_ADAPTER_ACCESSOR(public, public, bool, bold);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, filter);
	DEF_ADAPTER_ACCESSOR(public, public, double, alpha);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, mover);
public:
	explicit Label(System& system):
	Drawable(system){};
	virtual ~Label() noexcept = default;
	void incref(bool opt);
	void decref();
	virtual std::string inspect();
};

class Replace : public SystemItem
{
public:
	virtual void load(const std::string& _src, const std::string& _dest, bool _enabled, const std::string& _target, bool _fill, bool _partial, unsigned int _color, const std::string& _size, const std::string& _pos)
	{
		SET_PARAM(src);
		SET_PARAM(dest);
		SET_PARAM(enabled);
		SET_PARAM(target);
		SET_PARAM(fill);
		SET_PARAM(partial);
		SET_PARAM(color);
		SET_PARAM(size);
		SET_PARAM(pos);
	}
public:
	DEF_ADAPTER_ACCESSOR(public, public, std::string, src);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, dest);
	DEF_ADAPTER_ACCESSOR(public, public, bool, enabled);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, target);
	DEF_ADAPTER_ACCESSOR(public, public, bool, fill);
	DEF_ADAPTER_ACCESSOR(public, public, bool, partial);
	DEF_ADAPTER_ACCESSOR(public, public, unsigned int, color);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, size);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, pos);
public:
	enum{
		SAME_COLOR=0xffffffff
	};
	explicit Replace(System& system)
	:SystemItem(system), SET_DEFAULT(enabled, false){};
	virtual ~Replace() noexcept = default;
	void incref(bool opt);
	void decref();
	virtual std::string inspect();
};

//---------------------------------------------------------------------------------------------------------------------

class Message
{
public:
	enum Type{
		INVALID=0,
		COMMENT=1,
		SCRIPT=2
	};
	const enum Type type;
private:
	const double vpos_;
public:
	double vpos() const{return vpos_;};
private:
	Message():type(INVALID), vpos_(NAN){};
	Message(Message& other):type(INVALID), vpos_(NAN){};
	Message& operator = (Message& other){ return *this;};
protected:
	Message(enum Message::Type const type, float const vpos);
public:
	virtual ~Message(){};
	struct ComparatorByVpos
	{
		inline bool operator() (const Message& a, const Message& b) const { return a.vpos() < b.vpos(); };
		inline bool operator() (const Message& a, const float& b) const { return a.vpos() < b; };
		inline bool operator() (const float& a, const Message& b) const { return a < b.vpos(); };
		inline bool operator() (const std::shared_ptr<const Message>& a, const std::shared_ptr<const Message>& b) const { return a->vpos() < b->vpos(); };
		inline bool operator() (const std::shared_ptr<const Message>& a, const float& b) const { return a->vpos() < b; };
		inline bool operator() (const float& a, const std::shared_ptr<const Message>& b) const { return a < b->vpos(); };
	};
};

class Comment : public Message
{
private:
	const std::string message_;
	const bool isYourPost_;
	const std::string mail_;
	const bool fromButton_;
	const bool isPremium_;
	const unsigned int color_;
	const double size_;
	const unsigned int no_;
public:
	std::string message() const{return message_;};
	bool isYourPost() const{return isYourPost_;};
	std::string mail() const{return mail_;};
	bool fromButton() const{return fromButton_;};
	bool isPremium() const{return isPremium_;};
	unsigned int color() const{return color_;};
	double size() const{return size_;};
	unsigned int no() const{return no_;};
public:
	explicit Comment(const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no);
	virtual ~Comment(){};
};

class Script : public Message
{
public:
	explicit Script(const float vpos, std::shared_ptr<const tree::Node> node);
	virtual ~Script(){};
private:
	std::shared_ptr<const tree::Node> node_;
public:
	std::shared_ptr<const tree::Node> node() const{return node_;};
};

//----------------------------------------------------------------------------------------------------------------------

#define DEF_SYSTEM_LIST(clazz, name)\
private:\
	std::set<clazz*> name##List;\
public:\
	typedef std::set<clazz*>::const_iterator clazz##Iterator;\
	inline clazz##Iterator name##Begin() const\
	{\
		return name##List.begin();\
	}\
	inline clazz##Iterator name##End() const\
	{\
		return name##List.end();\
	}
class System
{
private:
	class EventEntry final{
	public:
		EventEntry(float const from, float const to, Handler<object::LazyEvalObject> obj);
		~EventEntry() = default;
	private:
		const float _from;
		const float _to;
		const Handler<object::LazyEvalObject> _obj;
	public:
		float from(){return _from;}
		float to(){return _to;}
		void eval();
		const tree::Location* location();
	};
public:
	logging::Logger& log;
	explicit System(logging::Logger& log);
	virtual ~System() = 0;
private:
	float _currentTime;
public:
	float currentTime(){return _currentTime;}
	void commentTrigger(float const timer, Handler<object::LazyEvalObject> obj);
	void timer(float const timer, Handler<object::LazyEvalObject> obj);
protected:
	void currentTime(float time){_currentTime=time;}
private:
	void dispatchCommentTrigger(machine::Machine& machine, std::shared_ptr<const Comment> comment);
	void dispatchCommentTrigger(machine::Machine& machine, const std::string& message, double vpos, bool isYourPost, const std::string& mail, bool fromButton, bool isPremium, unsigned int color, double size, unsigned int no);
	void dispatchTimer(machine::Machine& machine, const double to);
//---------------------------------------------------------------------------------------------------------------------
public: /* スクリプトから参照される */
	virtual Handler<Shape> drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
	virtual Handler<Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow);
	virtual void jumpCancel();
	virtual void seek(double vpos, const std::string& msg);
	virtual void addMarker(const std::string& name, double vpos);
	virtual double getMarker(const std::string& name);
	virtual Handler<Sum> sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial);
	virtual Handler<SumResult> showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, const std::vector<Handler<Sum> >& sum);
	virtual Handler<Replace> replace(const std::string& src, const std::string& dest, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, const std::string& size, const std::string& pos);
	virtual double screenWidth();
	virtual double screenHeight();
	virtual void addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden);
	virtual double playStartTime();
	virtual void BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume);
	virtual void playBGM(int id);
	virtual void stopBGM(int id);
	virtual void addAtPausePoint(double vpos, double wait);
	virtual void addPostRoute(const std::string& match, const std::string& id, const std::string& button);
	virtual void CM(const std::string& id, double time, bool pause, const std::string& link, double volume);
	virtual void playCM(int id);
public:
	DEF_ADAPTER_ACCESSOR(public, public, unsigned int, commentColor);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, commentPlace);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, commentSize);
	DEF_ADAPTER_ACCESSOR(public, public, bool, commentInvisible);
	DEF_ADAPTER_ACCESSOR(public, public, bool, commentReverse);
	DEF_ADAPTER_ACCESSOR(public, public, bool, defaultSage);
	DEF_ADAPTER_ACCESSOR(public, public, bool, postDisabled);
	DEF_ADAPTER_ACCESSOR(public, public, bool, seekDisabled);
	DEF_ADAPTER_ACCESSOR(public, public, bool, isLoaded);
	DEF_ADAPTER_ACCESSOR(public, public, bool, isWide);
	DEF_ADAPTER_ACCESSOR(public, public, std::string, lastVideo);
private:
	std::map<std::string, double> markerMap;
	std::set<Drawable*> drawableList;
	DEF_SYSTEM_LIST(Replace, replace);
public:
	void fetchDrawables(std::vector<Drawable*>& lst);
private:
	std::deque<std::shared_ptr<const Message> > messageQueue;
	std::multimap<float, std::shared_ptr<EventEntry>, std::less<float> > timerLine;
	std::multimap<float, std::shared_ptr<EventEntry>, std::less<float> > ctrigLine;
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
public: /* Nekomataから操作される */
	void seek(machine::Machine& machine, const double from, const double to);
	void queueMessage(std::shared_ptr<const Message> message);
protected: /* INFO: 各サブシステムで再実装すること。 */
	virtual std::string inspect();
	void onChanged();
};


#undef DEF_DRAWABLE_LIST
#undef DEF_SYSTEM_LIST
#undef DEF_ADAPTER_ACCESSOR
#undef SET_PARAM
#undef SET_DEFAULT

}}
