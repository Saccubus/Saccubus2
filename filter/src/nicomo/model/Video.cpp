/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include <cinamo/Logger.h>
#include <nicomo/model/Video.h>
#include <nicomo/model/Thread.h>
#include <nicomo/model/MetaInfo.h>
#include <nicomo/model/PlayInfo.h>

namespace nicomo {
namespace model {

const static std::string TAG("VideoContext");

Video::Video(cinamo::Logger& log)
:log(log)
,videofile_()
,metaInfo_(nullptr)
,playInfo_(nullptr)
{
	this->metaInfo(0);
	this->playInfo(0);
}

Video::~Video() {
	if(this->metaInfo()){
		delete this->metaInfo();
		metaInfo(nullptr);
	}
	if(this->playInfo()){
		delete this->playInfo();
		playInfo(nullptr);
	}
	for(std::map<unsigned long long, const Thread*>::const_iterator it = threadList.begin(); it != threadList.end();++it){
		delete it->second;
	}
	decltype(threadList)().swap(threadList);
}

void Video::initVideoFile(std::string const& videofile)
{
	this->videofile(videofile);
}

void Video::initPlayInfo(std::string const& playfile)
{
	this->playInfo(new PlayInfo(this->log, playfile));
}
void Video::initMetaInfo(std::string const& metafile)
{
	this->metaInfo(new MetaInfo(this->log, metafile));
}
void Video::initThread(std::vector<std::string>& threads)
{
	for(std::vector<std::string>::const_iterator it=threads.begin(); it != threads.end(); ++it){
		std::string const& th__ = *it;
		Thread* th = new Thread(this->log, th__);
		this->threadList.insert(std::pair<unsigned long long, const Thread*>(th->thread(), th));
	}
}

size_t Video::threadSize() const
{
	return threadList.size();
}
bool Video::hasThread(unsigned long long thread_id) const
{
	return threadList.find(thread_id) != threadList.end();
}
std::map<unsigned long long, const Thread*>::const_iterator Video::threadBegin() const
{
	return threadList.begin();
}
std::map<unsigned long long, const Thread*>::const_iterator Video::threadEnd() const
{
	return threadList.end();
}
const Thread* Video::thread(unsigned long long thread_id) const
{
	std::map<unsigned long long, const Thread*>::const_iterator it = threadList.find(thread_id);
	if(it == threadList.end()){
		log.w(TAG, "Thread id :%llu not found", thread_id);
		return 0;
	}else{
		return it->second;
	}
}

}}
