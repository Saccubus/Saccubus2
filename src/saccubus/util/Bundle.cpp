/*
 * Bundle.cpp
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "Bundle.h"
#include "./StringUtil.h"

namespace saccubus {
namespace util {

Bundle::Bundle() {
}

Bundle::~Bundle() {
}

void Bundle::readURLEncoded(const std::string& data)
{
	/* ☆車☆輪☆の☆再☆発☆明☆ */
	std::istringstream ss(data);
	std::string element;
	while(std::getline(ss, element, '&')){
		const size_t split = element.find("=");
		std::string key=element.substr(0, split);
		std::string val=element.substr(split+1);
		key = util::decodePercent(key);
		val = util::decodePercent(val);
		this->map.insert(std::pair<std::string, std::string>(key, val));
	}
}

size_t Bundle::size() const
{
	return map.size();
}

bool Bundle::has(const std::string& key) const
{
	return map.find(key) != map.end();
}
std::string Bundle::getString(const std::string& key) const
{
	std::map<std::string, std::string>::const_iterator val = map.find(key);
	if(val == map.end()){
		return std::string();
	}else{
		return val->second;
	}
}

long long Bundle::getLong(const std::string& key) const
{
	std::map<std::string, std::string>::const_iterator val = map.find(key);
	if(val == map.end()){
		return -1;
	}else{
		return std::strtoll(val->second.c_str(), 0, 10);
	}
}
bool Bundle::getBool(const std::string& key) const
{
	std::map<std::string, std::string>::const_iterator val = map.find(key);
	if(val == map.end()){
		return false;
	}else{
		std::string v(val->second);
		char* end;
		unsigned long num = strtol(v.c_str(), &end, 0);
		if(*end == '\0'){
			return num != 0;
		}else{
			std::transform(v.begin(), v.end(), v.begin(), ::tolower);
			return v == "true";
		}
	}
}

Bundle::Iterator Bundle::begin() const
{
	return map.begin();
}

Bundle::Iterator Bundle::end() const
{
	return map.end();
}

}}
