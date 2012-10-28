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

/**
 * ニワン語の一部として使えるようにエスケープする
 */
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

/**
 * ニワン語の一部として使えるようにエスケープする
 */
std::string escape(bool val)
{
	return val ? "true" : "false";
}

/**
 * 制御のための例外。
 * 正常に成功して大域脱出するために使う。
 * 正常なのに例外で制御？と思われると思いますが、
 * ANTLRの作者が言ってたので間違いないと思います（敬語）
 */
class FinishException : public std::exception
{

};
/**
 * 制御のための例外。
 * 正常なニコスクリプトの構文でないなどで失敗した事をしめす
 */
class FailException : public std::exception
{

};

NicosAction::NicosAction(const float vpos, const std::string& mail, const std::vector<std::string>& tokens)
:vpos(vpos), mail(mail), msgIndex(0), msgTokens(tokens)
{
}

NicosAction::~NicosAction() {
}

/**
 * すべてのアクションでこれを使う
 */
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
