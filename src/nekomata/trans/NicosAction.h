/**
 * Nekomata
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

#pragma once
#include <string>
#include <vector>
#include <cinamo/ClassUtil.h>
#include <nicomo/model/Comment.h>

namespace nekomata {
namespace trans {

std::string escape(const std::string& str);
std::string escape(bool val);

class NicosAction {
	DISABLE_COPY_AND_ASSIGN(NicosAction);
	DEFINE_MEMBER_REF(public, nicomo::model::Comment const, com)
private:
	std::size_t msgIndex;
	std::vector<std::string> msgTokens;
	std::string nextToken(bool require);
public:
	NicosAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens);
	virtual ~NicosAction() = 0;
public:
	std::string trans();
protected:
	virtual void read() = 0;
	virtual std::string write() = 0;
public:
	std::string commail(bool require=false);
	std::string string(bool require=false);
	bool visilibity(bool require=false);
	int times(bool require=false);
};

}}
