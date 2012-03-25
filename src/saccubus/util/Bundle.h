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
#include <vector>

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
	size_t size() const;
	bool has(const std::string& key) const;
	std::string getString(const std::string& key) const;
	long long getLong(const std::string& key) const;
	bool getBool(const std::string& key) const;
	Iterator begin() const;
	Iterator end() const;
};

}}
#endif /* BUNDLE_H_ */
