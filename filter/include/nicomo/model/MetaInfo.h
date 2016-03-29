/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <string>
#include <cinamo/ClassUtil.h>
#include <cinamo/Logger.h>
#include <tinyxml2.h>
#include "ReplaceTable.h"

namespace nicomo {
namespace model {

class MetaInfo final{
	DEFINE_MEMBER(public, private, std::string, title);
public:
	MetaInfo(cinamo::Logger& log, tinyxml2::XMLElement* elm);
	MetaInfo(cinamo::Logger& log, tinyxml2::XMLDocument* doc);
	MetaInfo(cinamo::Logger& log, const std::string& filename);
	~MetaInfo() = default;
private:
	void read(cinamo::Logger& log, tinyxml2::XMLElement* elm);
};

}}
