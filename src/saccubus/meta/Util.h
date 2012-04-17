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

#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <libxml2/libxml/tree.h>

namespace saccubus {
namespace meta {

template <typename T>
T readNodeProp(xmlNode* node, const std::string& name, const T& def);

template<>
std::string readNodeProp(xmlNode* node, const std::string& name, const std::string& def);

std::string readNodeProp(xmlNode* node, const std::string& name, const char* def);

template<>
float readNodeProp(xmlNode* node, const std::string& name, const float& def);

template<>
unsigned long long readNodeProp(xmlNode* node, const std::string& name, const unsigned long long& def);

template<>
long long readNodeProp(xmlNode* node, const std::string& name, const long long& def);

template<>
bool readNodeProp(xmlNode* node, const std::string& name, const bool& def);

bool compareNodeName(xmlNode* node, const std::string& name);

std::string readNodeContent(xmlNode* node);

}}
#endif /* UTIL_H_ */
