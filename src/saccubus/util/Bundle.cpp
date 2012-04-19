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

#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "Bundle.h"
#include "./StringUtil.h"
#include "../logging/Exception.h"

namespace saccubus {
namespace util {

Bundle::Bundle() {
}

Bundle::~Bundle() {
}

void Bundle::readURLEncoded(const std::string& data)
{
	/* ☆車☆輪☆の☆再☆発☆明☆ */
	std::vector<std::string> elements;
	util::split(data, "&", elements);
	for(std::vector<std::string>::const_iterator it = elements.begin(); it != elements.end(); ++it){
		const size_t split = it->find("=");
		std::string key=it->substr(0, split);
		std::string val=it->substr(split+1);
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
		throw logging::Exception(__FILE__, __LINE__, "There is no item for key: %s", key.c_str());
	}else{
		return val->second;
	}
}

long long Bundle::getLong(const std::string& key) const
{
	std::map<std::string, std::string>::const_iterator val = map.find(key);
	if(val == map.end()){
		throw logging::Exception(__FILE__, __LINE__, "There is no item for key: %s", key.c_str());
	}else{
		return std::strtoll(val->second.c_str(), 0, 10);
	}
}
bool Bundle::getBool(const std::string& key) const
{
	std::map<std::string, std::string>::const_iterator val = map.find(key);
	if(val == map.end()){
		throw logging::Exception(__FILE__, __LINE__, "There is no item for key: %s", key.c_str());
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

std::string Bundle::optString(const std::string& key, const std::string& def) const
{
	if(this->has(key)){
		return getString(key);
	}else{
		return def;
	}
}
long long Bundle::optLong(const std::string& key, long long def) const
{
	if(this->has(key)){
		return getLong(key);
	}else{
		return def;
	}
}
bool Bundle::optBool(const std::string& key, bool def) const
{
	if(this->has(key)){
		return getBool(key);
	}else{
		return def;
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
