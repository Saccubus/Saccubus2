/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "SaccubusOptions.h"

namespace saccubus {

ValueOption<std::string>::ValueOption(const std::string& name, std::string & stored)
:util::Option(name, util::Option::Normal, util::Option::Require)
,stored(stored)
{

}
ValueOption<std::string>::~ValueOption()
{

}

void ValueOption<std::string>::invoke(const std::string& name, const std::string* arg) {
	this->stored = *arg;
};

}
