/*
 * VideoInfo.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef VIDEOINFO_H_
#define VIDEOINFO_H_

#include <string>
#include <map>

namespace saccubus {
namespace meta {

class VideoInfo {
private:
	std::map<std::string, std::string> map;
public:
	VideoInfo(const std::string& info);
	virtual ~VideoInfo();
public:
	size_t size();
	bool has(const std::string& key);
	std::string getString(const std::string& key);
	int getInt(const std::string& key);
	bool getBool(const std::string& key);
};

}}
#endif /* VIDEOINFO_H_ */
