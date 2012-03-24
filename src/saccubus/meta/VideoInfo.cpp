/*
 * VideoInfo.cpp
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "VideoInfo.h"
#include "../util/StringUtil.h"

namespace saccubus {
namespace meta {

VideoInfo::VideoInfo(const std::string& info) {
	/* getflvの結果はPOSTと同じ形式で格納されているので、それを解除する車輪の再発明 */
	std::istringstream ss(info);
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

VideoInfo::~VideoInfo() {
}

size_t VideoInfo::size()
{
	return map.size();
}

bool VideoInfo::has(const std::string& key)
{
	return map.find(key) != map.end();
}
std::string VideoInfo::getString(const std::string& key)
{
	std::map<std::string, std::string>::iterator val = map.find(key);
	if(val == map.end()){
		return std::string();
	}else{
		return val->second;
	}
}

int VideoInfo::getInt(const std::string& key)
{
	std::map<std::string, std::string>::iterator val = map.find(key);
	if(val == map.end()){
		return -1;
	}else{
		return static_cast<int>(std::strtol(val->second.c_str(), 0, 10));
	}
}
bool VideoInfo::getBool(const std::string& key)
{
	std::map<std::string, std::string>::iterator val = map.find(key);
	if(val == map.end()){
		return false;
	}else{
		std::string v(val->second);
		std::transform(v.begin(), v.end(), v.begin(), ::tolower);
		return v == "true";
	}
}

}}
