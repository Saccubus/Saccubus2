/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "ButtonAction.h"
#include <sstream>

namespace saccubus {
namespace nicos {

ButtonAction::ButtonAction(layer::item::Comment const& com, const std::vector<std::string>& tokens)
:NicosAction(com, tokens)
,message_()
,commsg_()
,local_(true)
,commail_()
,times_(1)
{
}

ButtonAction::~ButtonAction() {
}

void ButtonAction::read()
{
	this->message_ = this->string(true);
	this->commsg_ = this->string();
	this->local_ = this->visilibity();
	this->commail_ = this->commail();
	this->times_ = this->times();
}

std::string ButtonAction::write()
{
	std::stringstream ss;
	ss << "addButton(";
	ss << "message:" << escape(message_) << ",";
	ss << "mail:" << escape(com().mail()) << ",";
	ss << "vpos:" << escape(com().vpos()) << ",";
	ss << "commes:" << escape(commsg_) << ",";
	ss << "commail:" << escape(commail_) << ",";
	ss << "comvisible:" << escape(local_) << ",";
	ss << "limit:" << escape(times_) << ")";
	std::string result = ss.str();

	return result;
}

}}
