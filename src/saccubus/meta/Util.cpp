/**
 * Saccubus
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

#include <algorithm>
#include <cstring>
#include "Util.h"
#include "../logging/Exception.h"

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
		unsigned long long res = strtoll(reinterpret_cast<const char*>(chr), 0, 0);
		xmlFree(chr);
		return res;
	}else{
		return def;
	}
}

template<>
long long readNodeProp(xmlNode* node, const std::string& name, const long long& def)
{
	xmlChar* chr = xmlGetProp(node, reinterpret_cast<const xmlChar*>(name.c_str()));
	if(chr){
		long long res = strtoll(reinterpret_cast<const char*>(chr), 0, 0);
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
		bool convSucceeded = *end == '\0';
		xmlFree(chr);
		if(convSucceeded){
			return num != 0;
		}
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str == "true";
	}else{
		return def;
	}
}

bool compareNodeName(xmlNode* node, const std::string& name)
{
	return xmlStrcmp(node->name, reinterpret_cast<const unsigned char*>(name.c_str())) == 0;
}

std::string readNodeContent(xmlNode* node)
{
	xmlChar* body = xmlNodeGetContent(node);
	if(!body){
		throw logging::Exception(__FILE__, __LINE__, "Invalid XML. Content for node(%s) not found.", node->name);
	}
	std::string msg (reinterpret_cast<char*>(body));
	xmlFree(body);
	return msg;
}
}}
