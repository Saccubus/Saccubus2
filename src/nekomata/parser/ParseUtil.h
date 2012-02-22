/*
 * ParseUtil.h
 *
 *  Created on: 2012/02/07
 *      Author: psi
 */

#ifndef PARSEUTIL_H_
#define PARSEUTIL_H_

#include <string>
#include <antlr3.h>
#include "../logging/Logging.h"
#include "../tree/Node.h"
#include <tr1/memory>
namespace nekomata{
namespace parse{

const std::string createStringFromString(pANTLR3_STRING string);
const std::string createStringFromToken(pANTLR3_COMMON_TOKEN tok);
const logging::Location createLocationFromNode(std::tr1::shared_ptr<const tree::Node> node);
const logging::Location createLocationFromToken(pANTLR3_COMMON_TOKEN tok);
}
}


#endif /* PARSEUTIL_H_ */
