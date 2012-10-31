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
#pragma once
#include <string>
#include <map>
#include <vector>

namespace saccubus {
namespace util {

class Bundle {
private:
	std::map<std::string, std::string> map;
public:
	Bundle();
	virtual ~Bundle();
public:
	void readURLEncoded(const std::string& data);
	typedef std::map<std::string, std::string>::const_iterator Iterator;
	size_t size() const;
	bool has(const std::string& key) const;
	std::string getString(const std::string& key) const;
	std::string optString(const std::string& key, const std::string& def) const;
	long long getLong(const std::string& key) const;
	long long optLong(const std::string& key, long long def) const;
	bool getBool(const std::string& key) const;
	bool optBool(const std::string& key, bool def) const;
	Iterator begin() const;
	Iterator end() const;
};

}}
