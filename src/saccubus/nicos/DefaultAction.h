/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include "NicosAction.h"

namespace saccubus {
namespace nicos {

class DefaultAction: public NicosAction {
public:
	DefaultAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens);
	virtual ~DefaultAction();
protected:
	virtual void read();
	virtual std::string write();
private:
	std::string message_;
	std::string commsg_;
	bool local_;
	std::string commail_;
	int times_;
};

}}
