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

#include "NicosAction.h"
#include <exception>
#include <cstdlib>
#include <sstream>

namespace nekomata {
namespace trans {

std::string escape(const std::string& str)
{
	std::stringstream ss;
	size_t idx;
	size_t last = 0;
	ss << "\"";
	while(((idx = str.find_first_of("\"\'\\", last)) != std::string::npos) && idx < str.size()-1){
		ss << str.substr(last, idx-last);
		ss << "\\";
		ss << str.substr(idx, 1);
		last = ++idx;
	}
	ss << str.substr(last);
	ss << "\"";
	return ss.str();
}

std::string escape(bool val)
{
	return val ? "true" : "false";
}

class FinishException : public std::exception
{

};
class FailException : public std::exception
{

};

NicosAction::NicosAction(const float vpos, const std::string& mail, const std::vector<std::string>& tokens)
:vpos(vpos), mail(mail), msgIndex(0), msgTokens(tokens)
{
}

NicosAction::~NicosAction() {
}

std::string NicosAction::trans()
{
	try{
		read();
	} catch (FinishException& e) {

	} catch (FailException& e) {
		return "";
	}
	return write();
}

bool NicosAction::visilibity(bool require)
{
	std::string token = nextToken(require);
	if(token == "表示"){
		return true;
	}else{
		return false;
	}
}
int NicosAction::times(bool require)
{
	std::string token = nextToken(require);
	int ret = std::strtol(token.c_str(), 0, 10);
	return ret;
}

std::string NicosAction::nextToken(bool require)
{
	if(this->msgIndex >= this->msgTokens.size()){
		if(require){
			throw FailException();
		}else{
			throw FinishException();
		}
	}
	return this->msgTokens.at(this->msgIndex++);
}

std::string NicosAction::string(bool require)
{
	return nextToken(require);
}

std::string NicosAction::commail(bool require)
{
	std::string str = nextToken(require);
	std::stringstream ss;
	size_t idx;
	size_t last = 0;
	while(((idx = str.find(",", last)) != std::string::npos) && idx < str.size()-1){
		if(last > 0){
			ss << " ";
		}
		ss << str.substr(last, idx-last);
		last = ++idx;
	}
	ss << str.substr(last);
	return ss.str();
}

}}
