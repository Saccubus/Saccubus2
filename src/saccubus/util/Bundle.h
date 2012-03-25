/*
 * Bundle.h
 *
 *  Created on: 2012/03/25
 *      Author: psi
 */

#ifndef BUNDLE_H_
#define BUNDLE_H_

#include <string>
#include <map>

namespace saccubus {
namespace util {

class Bundle {
private:
	std::map<std::string, std::string> map;
private:
	Bundle();
public:
	static Bundle fromFormEncoded(const std::string& data);
	virtual ~Bundle();
public:
	typedef std::map<std::string, std::string>::const_iterator Iterator;
	size_t size();
	bool has(const std::string& key);
	std::string getString(const std::string& key);
	long long getLong(const std::string& key);
	bool getBool(const std::string& key);
	Iterator begin();
	Iterator end();
};

}}
#endif /* BUNDLE_H_ */
