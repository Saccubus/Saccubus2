/*
 * TestCommon.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef TESTCOMMON_H_
#define TESTCOMMON_H_

#include <gtest/gtest.h>
#include <iostream>
#include "../../saccubus/logging/Exception.h"
#include "../../saccubus/logging/Logger.h"
using namespace saccubus::logging;

#define MATERIAL_DIR "_TestMaterials/"

#define NULL_STREAM (*((std::ostream*)0))
static Logger log_trace(std::cout, Logger::TRACE_);
static Logger log_err(std::cout, Logger::ERROR_);

#define MOCK_ACCESSOR_EXPAND(super, type, name)\
public:\
	type name() {return this->super::name(); }\
	void name(type const& val) { this->super::name(val); }

#endif /* TESTCOMMON_H_ */
