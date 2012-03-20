/*
 * ParseUtil.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
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

const std::string createStringFromString(pANTLR3_STRING string);
const std::string createStringFromToken(pANTLR3_COMMON_TOKEN tok);
const tree::Location createLocationFromNode(std::tr1::shared_ptr<const tree::Node> node);
const tree::Location createLocationFromToken(pANTLR3_COMMON_TOKEN tok);

}
}
}

#endif /* PARSEUTIL_H_ */
