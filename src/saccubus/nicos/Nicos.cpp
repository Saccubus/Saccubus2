/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2012-2013, PSI
 */

#include "Nicos.h"
#include <cinamo/functional/Parser.h>

namespace saccubus {
namespace nicos {

Nicos::Nicos()
{
}

std::vector<std::pair<enum Token, std::string> > Nicos::parse(std::string const& string)
{
	using namespace cinamo::parser;
	//ParserCombinator<
	//>
}

}}
