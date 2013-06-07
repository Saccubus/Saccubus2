/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "ButtonAction.h"
#include <sstream>

namespace nekomata {
namespace trans {

ButtonAction::ButtonAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens)
:NicosAction(com, tokens)
,_message()
,_commsg()
,_local(true)
,_commail()
,_times(1)
{
}

ButtonAction::~ButtonAction() {
}

void ButtonAction::read()
{
	this->_message = this->string(true);
	this->_commsg = this->string();
	this->_local = this->visilibity();
	this->_commail = this->commail();
	this->_times = this->times();
}

std::string ButtonAction::write()
{
	std::stringstream ss;
	ss << "addButton(";
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
