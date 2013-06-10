/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2012-2013, PSI
 */


#pragma once
#include <string>
#include <vector>
#include <utility>

namespace saccubus {
namespace nicos {

enum Token {
	String=0,
	Number=1
};

class Nicos final{
public:
	Nicos();
	~Nicos() = default;
public:
	std::vector<std::pair<enum Token, std::string> > parse(std::string const& string);
};

}}
