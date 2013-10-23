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
	FunctionOption(std::string const& name, std::function<void()> func)
	:util::Option(name, util::Option::Normal, util::Option::No)
	,func(func){};
	virtual ~FunctionOption(){};
public:
	virtual void invoke(std::string const& name, const std::string* arg) {func();} ;
};

template <typename T>
class FlagOption : public util::Option
{
private:
	T & stored;
	const T val;
public:
	FlagOption(std::string const& name, T & stored, T val)
	:util::Option(name, util::Option::Normal, util::Option::No)
	,stored(stored)
	,val(val)
	{}
	virtual ~FlagOption(){};
public:
	virtual void invoke(std::string const& name, const std::string* arg) { this->stored = val; } ;
};

template <typename T>
class ValueOption : public util::Option
{
public:
	ValueOption(std::string const& name, T & stored);
	virtual ~ValueOption();
};

template <>
class ValueOption<std::string> : public util::Option
{
private:
	std::string & stored;
public:
	ValueOption(std::string const& name, std::string & stored);
	virtual ~ValueOption();
	virtual void invoke(std::string const& name, const std::string* arg);
};

template<class T>
class PreifxOption : public util::Option
{
private:
	T& map;
public:
	PreifxOption(std::string const& name, T& map)
	:util::Option(name, util::Option::Prefix, util::Option::Require)
	,map(map){}
	virtual ~PreifxOption(){}
public:
	virtual void invoke(std::string const& name, const std::string* arg)
	{
		map.insert(std::pair<std::string, std::string>(name.substr(this->name().size()),*arg));
	}
};

}

