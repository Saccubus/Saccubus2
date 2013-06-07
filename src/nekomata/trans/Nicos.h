/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */


#pragma once
#include <string>
#include <vector>
#include <utility>

namespace nekomata {
namespace trans {

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
