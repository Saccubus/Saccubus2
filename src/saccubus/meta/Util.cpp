/*
 * Util.cpp
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#include <algorithm>
#include <cstring>
#include "Util.h"

namespace saccubus {
namespace meta {

template<>
std::string readNodeProp(xmlNode* node, const std::string& name, const std::string& def)
{
	xmlChar* chr = xmlGetProp(node, reinterpret_cast<const xmlChar*>(name.c_str()));
	if(chr){
		std::string res(reinterpret_cast<const char*>(chr));
		xmlFree(chr);
		return res;
	}else{
		return def;
	}
}

std::string readNodeProp(xmlNode* node, const std::string& name, const char* def){
	return readNodeProp(node,name, std::string(def));
}


template<>
float readNodeProp(xmlNode* node, const std::string& name, const float& def)
{
	xmlChar* chr = xmlGetProp(node, reinterpret_cast<const xmlChar*>(name.c_str()));
	if(chr){
		float res = strtof(reinterpret_cast<const char*>(chr), 0);
		xmlFree(chr);
		return res;
	}else{
		return def;
	}
}

template<>
unsigned long long readNodeProp(xmlNode* node, const std::string& name, const unsigned long long& def)
{
	xmlChar* chr = xmlGetProp(node, reinterpret_cast<const xmlChar*>(name.c_str()));
	if(chr){
		unsigned long long res = strtoll(reinterpret_cast<const char*>(chr), 0, 10);
		xmlFree(chr);
		return res;
	}else{
		return def;
	}
}

template<>
bool readNodeProp(xmlNode* node, const std::string& name, const bool& def)
{
	xmlChar* chr = xmlGetProp(node, reinterpret_cast<const xmlChar*>(name.c_str()));
	if(chr){
		char* end;
		std::string str(reinterpret_cast<const char*>(chr));
		unsigned long long num = strtoll(reinterpret_cast<const char*>(chr), &end, 10);
		xmlFree(chr);
		if(*end == '\0'){
			return num != 0;
		}
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str == "true";
	}else{
		return def;
	}
}


}}
