/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#pragma once
#include <stdio.h>
#include <gtest/gtest.h>

#include <memory>
using std::shared_ptr;
#include <iostream>
#include <cinamo/Logger.h>
#include "../src/saccubus/logging/Exception.h"
using namespace saccubus::logging;

#define MATERIAL_DIR "_TestMaterials/"

#define NULL_STREAM (*((std::ostream*)0))
static cinamo::Logger log_trace(std::cout, cinamo::Logger::TRACE_);
static cinamo::Logger log_err(std::cout, cinamo::Logger::ERROR_);

#define MOCK_ACCESSOR_EXPAND(super, type, name)\
public:\
	type name() {return this->super::name(); }\
	void name(type const& val) { this->super::name(val); }

