/*
 * VideoContext.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "VideoContext.h"
#include "../logging/Logger.h"
#include "Thread.h"
#include "MetaInfo.h"
#include "PlayInfo.h"

namespace saccubus {
namespace meta {

const static std::string TAG("VideoContext");

VideoContext::VideoContext(logging::Logger& log)
:log(log)
{
	this->metaInfo(0);
	this->playInfo(0);
}

VideoContext::~VideoContext() {
	if(this->metaInfo()){
		delete this->metaInfo();
	}
	if(this->playInfo()){
		delete this->playInfo();
	}
	for(std::map<unsigned long long, const Thread*>::const_iterator it = threadList.begin(); it != threadList.end();++it){
		delete it->second;
	}
	threadList.clear();
}

void VideoContext::initVideoFile(const std::string& videofile)
{
	this->videofile(videofile);
}

void VideoContext::initPlayInfo(const std::string& playfile)
{
	this->playInfo(new PlayInfo(this->log, playfile));
}
void VideoContext::initMetaInfo(const std::string& metafile)
{
	this->metaInfo(new MetaInfo(this->log, metafile));
}
void VideoContext::initThread(std::vector<std::string>& threads)
{
	for(std::vector<std::string>::const_iterator it=threads.begin(); it != threads.end(); ++it){
		Thread* th = new Thread(this->log, *it);
		this->threadList.insert(std::pair<unsigned long long, const Thread*>(th->thread(), th));
	}
}

size_t VideoContext::threadSize() const
{
	return threadList.size();
}
bool VideoContext::hasThread(unsigned long long thread_id) const
{
	return threadList.find(thread_id) != threadList.end();
}
std::map<unsigned long long, const Thread*>::const_iterator VideoContext::threadBegin() const
{
	return threadList.begin();
}
std::map<unsigned long long, const Thread*>::const_iterator VideoContext::threadEnd() const
{
	return threadList.end();
}
const Thread* VideoContext::thread(unsigned long long thread_id) const
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
