/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <string>
#include <antlr3.h>
#include <sstream>
#include "../tree/Node.h"
#include "ParseUtil.h"

using std::shared_ptr;
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
const tree::Location createLocationFromToken(pANTLR3_COMMON_TOKEN tok){
	return tree::Location(createStringFromString(tok->input->fileName), tok->getLine(tok), tok->getCharPositionInLine(tok), createStringFromToken(tok));
}
const tree::Location createLocationFromNode(std::shared_ptr<const tree::Node> node){
	return tree::Location(node->location());
}

std::string unescapeString(std::string const& str){
	std::stringstream ss;
	size_t last = 0;
	size_t idx;
	while(((idx = str.find("\\", last)) != std::string::npos) && (idx < str.size()-1) ){
		ss << str.substr(last, (idx-last));
		std::string tmp(ss.str());
		switch(str.at(++idx)){
		case 'n':
			ss << "\n";
			break;
		case 'r':
			ss << "\r";
			break;
		case 't':
			ss << "\t";
			break;
		case 'b':
			ss << "\b";
			break;
		case 'f':
			ss << "\f";
			break;
		case '\"':
			ss << "\"";
			break;
		case '\'':
			ss << "\'";
			break;
		case '\\':
			ss << "\\";
			break;
		default:
			ss << "\\";
			ss << str.at(idx);
			break;
		}
		last = idx+1;
	}
	ss << str.substr(last);
	std::string result = ss.str();
	return result;
}

}}}
