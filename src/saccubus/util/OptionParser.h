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

#ifndef Saccubus_OPTIONPARSER_H__CPP_
#define Saccubus_OPTIONPARSER_H__CPP_

#include <vector>
#include <string>
#include "ClassAccessor.h"

/**
 * FIXME: これはひどい車輪の再発明
 */

namespace saccubus {
namespace util {

class Option {
public:
	enum Type {
		Normal,
		Prefix
	};
	enum Argument{
		No,
		Require,
		Optional
	};
	DEF_ATTR_ACCESSOR(public, private, std::string, name);
	DEF_ATTR_ACCESSOR(public, private, enum Type, type);
	DEF_ATTR_ACCESSOR(public, private, enum Argument, argument);
protected:
	Option(const std::string& name, enum Type t, enum Argument a);
public:
	virtual ~Option();
public:
	virtual void invoke(const std::string& name, const std::string* arg) = 0;
};

class OptionParser {
	std::vector<Option*> opts;
public:
	OptionParser();
	virtual ~OptionParser();
public:
	void add(Option* opt);
	void parse(int argc, char** argv, std::vector<std::string>& left);
};

}}
#endif /* INCLUDE_GUARD */
