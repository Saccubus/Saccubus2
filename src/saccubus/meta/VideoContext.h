/*
 * VideoContext.h
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#ifndef VIDEOCONTEXT_H_
#define VIDEOCONTEXT_H_

#include <map>
#include <vector>
#include <string>
#include "../util/ClassAccessor.h"
#include "../classdefs.h"

namespace saccubus {
namespace meta {

class VideoContext {
	DEF_ATTR_ACCESSOR(public, private, std::string, videofile);
	DEF_ATTR_ACCESSOR(public, private, const MetaInfo*, metaInfo);
	DEF_ATTR_ACCESSOR(public, private, const PlayInfo*, playInfo);
	std::map<unsigned long long, const Thread*> threadList;
private:
	logging::Logger& log;
public:
	VideoContext(logging::Logger& log);
	virtual ~VideoContext();
public:
	void init(const std::string& videofile, const std::string& metafile, const std::string& playfile, const std::vector<std::string>& threadfiles);
public:
	size_t threadSize() const;
	bool hasThread(unsigned long long thread_id) const;
	std::map<unsigned long long, const Thread*>::const_iterator threadBegin() const;
	std::map<unsigned long long, const Thread*>::const_iterator threadEnd() const;
	const Thread* thread(unsigned long long thread_id) const;
};

}}
#endif /* VIDEOCONTEXT_H_ */
