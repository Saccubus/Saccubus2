/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <string>
#include <memory>
#include <antlr3.h>
#include <nekomata/classdefs.h>

#include "../tree/Location.h"

namespace nekomata{
namespace parser{
namespace util{

const std::string createStringFromString(pANTLR3_STRING string);
const std::string createStringFromToken(pANTLR3_COMMON_TOKEN tok);
const tree::Location createLocationFromNode(std::shared_ptr<const tree::Node> node);
const tree::Location createLocationFromToken(pANTLR3_COMMON_TOKEN tok);
std::string unescapeString(std::string const& str);

}}}
