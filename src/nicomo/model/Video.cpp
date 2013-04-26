/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
