/*
 * VideoContext.cpp
 *
 *  Created on: 2012/04/01
 *      Author: psi
 */

#include "Video.h"
#include "../logging/Logger.h"
#include "Thread.h"
#include "MetaInfo.h"
#include "PlayInfo.h"

namespace saccubus {
namespace meta {

const static std::string TAG("VideoContext");

Video::Video(logging::Logger& log)
:log(log)
{
	this->metaInfo(0);
	this->playInfo(0);
}

Video::~Video() {
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

void Video::initVideoFile(const std::string& videofile)
{
	this->videofile(videofile);
}

void Video::initPlayInfo(const std::string& playfile)
{
	this->playInfo(new PlayInfo(this->log, playfile));
}
void Video::initMetaInfo(const std::string& metafile)
{
	this->metaInfo(new MetaInfo(this->log, metafile));
}
void Video::initThread(std::vector<std::string>& threads)
{
	for(std::vector<std::string>::const_iterator it=threads.begin(); it != threads.end(); ++it){
		Thread* th = new Thread(this->log, *it);
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