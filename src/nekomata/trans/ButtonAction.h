/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include "NicosAction.h"

namespace nekomata {
namespace trans {

class ButtonAction: public nekomata::trans::NicosAction {
public:
	ButtonAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens);
	virtual ~ButtonAction();
protected:
	virtual void read();
	virtual std::string write();
private:
	std::string _message;
	std::string _commsg;
	bool _local;
	std::string _commail;
	int _times;
};

}}
