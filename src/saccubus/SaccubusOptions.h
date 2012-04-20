/**
 * Saccubus
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

#ifndef Saccubus_SACCUBUS_OPTIONS_H__CPP_
#define Saccubus_SACCUBUS_OPTIONS_H__CPP_

#include <tr1/functional>
#include <map>
#include "logging/Logger.h"
#include "util/OptionParser.h"

namespace saccubus {

class LoglevelOption : public util::Option
{
private:
	logging::Logger::Level const level;
	logging::Logger::Level* const stored;
public:
	LoglevelOption(const std::string& name, logging::Logger::Level level, logging::Logger::Level* stored)
	:util::Option(name, util::Option::Normal, util::Option::No)
	,level(level),stored(stored){}
	virtual ~LoglevelOption(){};
public:
	virtual void invoke(const std::string& name, const std::string* arg){*stored=level;};
};

class FuncOption : public util::Option
{
public:
	typedef std::tr1::function<void()> Func;
private:
	Func const func;
public:
	FuncOption(const std::string& name, Func func)
	:util::Option(name, util::Option::Normal, util::Option::No)
	,func(func){};
	virtual ~FuncOption(){};
public:
	virtual void invoke(const std::string& name, const std::string* arg) {func();} ;
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

#endif /* INCLUDE_GUARD */
