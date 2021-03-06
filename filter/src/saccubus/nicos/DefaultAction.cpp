/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2012-2013, PSI
 */

#include "DefaultAction.h"
#include <sstream>

namespace saccubus {
namespace nicos {

DefaultAction::DefaultAction(layer::item::Comment const& com, const std::vector<std::string>& tokens)
:NicosAction(com, tokens)
,message_()
,commsg_()
,local_(true)
,commail_()
,times_(1)
{
}

DefaultAction::~DefaultAction() {
}

void DefaultAction::read()
{
	this->message_ = this->string(true);
	this->commsg_ = this->string();
	this->local_ = this->visilibity();
	this->commail_ = this->commail();
	this->times_ = this->times();
}

std::string DefaultAction::write()
{
	std::stringstream ss;
	ss << "addDefault(";
	ss << "message:" << escape(message_) << ",";
	ss << "mail:" << escape(com().mail()) << ",";
	ss << "vpos:" << escape(com().vpos()) << ",";
	ss << "commes:" << escape(commsg_) << ",";
	ss << "commail:" << escape(commail_) << ",";
	ss << "comvisible:" << escape(local_) << ",";
	ss << "limit:" << escape(times_) << ")";
	return ss.str();
}

}}
