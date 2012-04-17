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

#ifndef Saccubus_COMMENTPROCESSINGFLOW_H__CPP_
#define Saccubus_COMMENTPROCESSINGFLOW_H__CPP_

#include "Comment.h"
#include "../NekomataLayer.h"

namespace saccubus {
namespace layer {
namespace item {

struct MailOperation{
public:
	enum Permission{
		Normal=0,
		Premium = 1,
	};
	enum ArgType{
		Exactly,
		StartsWith
	};
public:
	const enum ArgType argType;
	const std::string name;
	const enum Permission permission;
	typedef std::tr1::function<bool(const std::string& name, Comment* comment)> Func;
	const Func func;
	MailOperation(const enum ArgType argType, const std::string& name, const enum Permission permission, Func func)
	:argType(argType), name(name), permission(permission), func(func){};
	virtual ~MailOperation(){};
	bool execute(const std::string& command, Comment* comment) const;
private:
	static const struct MailOperation Instance[];
	static const size_t Count;
public:
	static bool apply(const std::string& mail, Comment* product);
};

class CommentPipeLine {
private:
	logging::Logger& log;
public:
	meta::ReplaceTable* replaceTable;
	NekomataLayer* nekomataLayer;
public:
	CommentPipeLine(logging::Logger& log, meta::ReplaceTable* replaceTable, NekomataLayer* nekomataLayer);
	virtual ~CommentPipeLine();
public:
	Comment* process(const meta::Comment* comment);
};

}}}
#endif /* INCLUDE_GUARD */
