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

#ifndef Saccubus_MESSAGEORGANIZEROPERATION_H__CPP_
#define Saccubus_MESSAGEORGANIZEROPERATION_H__CPP_

#include <tr1/functional>
#include <nekomata/system/System.h>
#include "../classdefs.h"

namespace saccubus {
namespace layer {

struct MailOperation{
public:
	enum Permission {
		Normal=0,
		Premium = 1,
		Forked = 2
	};
	enum ArgType {
		Exactly,
		StartsWith
	};
public:
	const enum ArgType argType;
	const std::string name;
	const enum Permission permission;
	typedef std::tr1::function<bool(const std::string& name, item::Comment* comment)> Func;
	const Func func;
	MailOperation(const enum ArgType argType, const std::string& name, const enum Permission permission, Func func)
	:argType(argType), name(name), permission(permission), func(func){};
	virtual ~MailOperation(){};
	bool execute(const std::string& command, item::Comment* comment) const;
private:
	static const struct MailOperation Instance[];
	static const size_t Count;
public:
	static bool apply(const std::string& mail, item::Comment* product);
};

struct NekomataReplaceOperation
{
public:
	static void apply(nekomata::system::Replace* replace, item::Comment* comment);
	static void apply(nekomata::system::System* system, item::Comment* comment);
};

}}
#endif /* INCLUDE_GUARD */
