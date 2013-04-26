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

#include "DefaultAction.h"
#include <sstream>

namespace nekomata {
namespace trans {

DefaultAction::DefaultAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens)
:NicosAction(com, tokens)
,_message()
,_commsg()
,_local(true)
,_commail()
,_times(1)
{
}

DefaultAction::~DefaultAction() {
}

void DefaultAction::read()
{
	this->_message = this->string(true);
	this->_commsg = this->string();
	this->_local = this->visilibity();
	this->_commail = this->commail();
	this->_times = this->times();
}

std::string DefaultAction::write()
{
	std::stringstream ss;
	ss << "addDefault(";
	ss << "message:" << escape(_message) << ",";
	ss << "mail:" << escape(com().mail()) << ",";
	ss << "vpos:" << com().vpos() << ",";
	ss << "commes:" << escape(_commsg) << ",";
	ss << "commail:" << escape(_commail) << ",";
	ss << "comvisible:" << escape(_local) << ",";
	ss << "limit:" << _times << ")";
	std::string result = ss.str();

	return result;
}

}}
