/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Logger.h>
#include <functional>
#include <map>
#include "util/OptionParser.h"

namespace saccubus {

class FunctionOption : public util::Option
{
private:
	std::function<void()> const func;
public:
	FunctionOption(const std::string& name, std::function<void()> func)
	:util::Option(name, util::Option::Normal, util::Option::No)
	,func(func){};
	virtual ~FunctionOption(){};
public:
	virtual void invoke(const std::string& name, const std::string* arg) {func();} ;
};

template <typename T>
class FlagOption : public util::Option
{
private:
	T & stored;
	const T val;
public:
	FlagOption(const std::string& name, T & stored, T val)
	:util::Option(name, util::Option::Normal, util::Option::No)
	,stored(stored)
	,val(val)
	{}
	virtual ~FlagOption(){};
public:
	virtual void invoke(const std::string& name, const std::string* arg) { this->stored = val; } ;
};

template <typename T>
class ValueOption : public util::Option
{
public:
	ValueOption(const std::string& name, T & stored);
	virtual ~ValueOption();
};

template <>
class ValueOption<std::string> : public util::Option
{
private:
	std::string & stored;
public:
	ValueOption(const std::string& name, std::string & stored);
	virtual ~ValueOption();
	virtual void invoke(const std::string& name, const std::string* arg);
};

template<class T>
class PreifxOption : public util::Option
{
private:
	T& map;
public:
	PreifxOption(const std::string& name, T& map)
	:util::Option(name, util::Option::Prefix, util::Option::Require)
	,map(map){}
	virtual ~PreifxOption(){}
public:
	virtual void invoke(const std::string& name, const std::string* arg)
	{
		map.insert(std::pair<std::string, std::string>(name.substr(this->name().size()),*arg));
	}
};

}

