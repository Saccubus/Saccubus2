/*
 * ParserUtil.cpp
 *
 *  Created on: 2012/02/08
 *      Author: psi
 */

#include <string>
#include <antlr3.h>
#include "../logging/Logging.h"
#include "ParseUtil.h"

using std::tr1::shared_ptr;
namespace nekomata{
namespace parser{
namespace util{


const std::string createStringFromString(pANTLR3_STRING string){
	if(string->encoding != ANTLR3_ENC_UTF8){
		pANTLR3_STRING str = string->toUTF8(string);
		return std::string(reinterpret_cast<const char*>(str->chars));
	}
	return std::string(reinterpret_cast<const char*>(string->chars));
}
const std::string createStringFromToken(pANTLR3_COMMON_TOKEN tok){
	return createStringFromString(tok->getText(tok));
}
const logging::Location createLocationFromToken(pANTLR3_COMMON_TOKEN tok){
	return logging::Location(createStringFromString(tok->input->fileName), tok->getLine(tok), tok->getCharPositionInLine(tok), createStringFromToken(tok));
}
const logging::Location createLocationFromNode(std::tr1::shared_ptr<const tree::Node> node){
	return logging::Location(node->location());
}

}}}
