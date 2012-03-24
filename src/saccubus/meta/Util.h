/*
 * Util.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
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
bool readNodeProp(xmlNode* node, const std::string& name, const bool& def);


}}
#endif /* UTIL_H_ */
