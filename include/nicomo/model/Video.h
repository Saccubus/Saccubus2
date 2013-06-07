/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <map>
#include <vector>
#include <string>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>

namespace nicomo {
namespace model {

class MetaInfo;
class PlayInfo;
class Thread;

class Video {
private:
	cinamo::Logger& log;
	DEFINE_MEMBER(public, private, std::string, videofile);
	DEFINE_MEMBER(public, private, const MetaInfo*, metaInfo);
	DEFINE_MEMBER(public, private, const PlayInfo*, playInfo);
private:
	std::map<unsigned long long, const Thread*> threadList;
public:
	Video(cinamo::Logger& log);
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
