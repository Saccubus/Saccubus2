/*
 * VideoContext.h
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include <map>
#include <vector>
#include <string>
#include "../util/ClassAccessor.h"
#include "../classdefs.h"

namespace saccubus {
namespace meta {

class Video {
	DEF_ATTR_ACCESSOR(public, private, std::string, videofile);
	DEF_ATTR_ACCESSOR(public, private, const MetaInfo*, metaInfo);
	DEF_ATTR_ACCESSOR(public, private, const PlayInfo*, playInfo);
	std::map<unsigned long long, const Thread*> threadList;
private:
	logging::Logger& log;
public:
	Video(logging::Logger& log);
	virtual ~Video();
public:
	void initVideoFile(const std::string& videofile);
	void initPlayInfo(const std::string& metafile);
	void initMetaInfo(const std::string& metafile);
	void initThread(std::vector<std::string>& threads);
public:
	typedef std::map<unsigned long long, const Thread*>::const_iterator ThreadIterator;
	size_t threadSize() const;
	bool hasThread(unsigned long long thread_id) const;
	ThreadIterator threadBegin() const;
	ThreadIterator threadEnd() const;
	const Thread* thread(unsigned long long thread_id) const;
};

}}
#endif /* VIDEO_H_ */
