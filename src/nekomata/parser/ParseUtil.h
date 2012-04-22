/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PARSEUTIL_H_
#define PARSEUTIL_H_

#include <string>
#include <tr1/memory>
#include <antlr3.h>
#include <nekomata/classdefs.h>

#include "../tree/Location.h"

namespace nekomata{
namespace parser{
namespace util{

const std::string unescapeString(const std::string& str);
const std::string createStringFromString(pANTLR3_STRING string);
const std::string createStringFromToken(pANTLR3_COMMON_TOKEN tok);
const tree::Location createLocationFromNode(std::tr1::shared_ptr<const tree::Node> node);
const tree::Location createLocationFromToken(pANTLR3_COMMON_TOKEN tok);

}}}
#endif /* PARSEUTIL_H_ */
