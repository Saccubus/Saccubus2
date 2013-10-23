/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2012-2013, PSI
 */

#include "NicosAction.h"
#include <cinamo/String.h>
#include <exception>
#include <cstdlib>
#include <sstream>

namespace saccubus {
namespace nicos {

/**
 * ニワン語の一部として使えるようにエスケープする
 */
std::string escape(std::string const& str)
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

std::string escape(int val)
{
	return cinamo::format("%d", val);
}
std::string escape(float val)
{
	return cinamo::format("%f", val);
}

/**
 * 制御のための例外。
 * 正常に成功して大域脱出するために使う。
 * 正常なのに例外で制御？と思われると思いますが、
 * ANTLRの作者が言ってたので間違いないと思います（敬語）
 */
class FinishException final : public std::exception
{

};
/**
 * 制御のための例外。
 * 正常なニコスクリプトの構文でないなどで失敗した事をしめす
 */
class FailException final : public std::exception
{

};

NicosAction::NicosAction(layer::item::Comment const& com, const std::vector<std::string>& tokens)
:com_(com)
,msgIndex_(0)
,msgTokens_(tokens)
,mailTokens_(cinamo::splitSpace(com.mail()))
{
	for( std::string& tk : mailTokens_ ){
		tk = cinamo::trim(tk);
	}
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

bool NicosAction::hasMail(std::string const& token) const
{
	for(std::string const& tok : mailTokens_) {
		if(tok == token) {
			return true;
		}
	}
	return false;
}

bool NicosAction::visilibity(bool require)
{
	std::string token = nextToken(require);
	return token == "表示" ? true : false;
}
int NicosAction::times(bool require)
{
	return std::strtol(nextToken(require).c_str(), 0, 10);
}

std::string NicosAction::nextToken(bool require)
{
	if(this->msgIndex_ >= this->msgTokens_.size()){
		if(require){
			throw FailException();
		}else{
			throw FinishException();
		}
	}
	return this->msgTokens_.at(this->msgIndex_++);
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
