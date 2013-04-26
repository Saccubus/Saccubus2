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

#include <algorithm>
#include <cinamo/Exception.h>
#include <cinamo/XMLAttrParser.h>
#include <nicomo/model/Thread.h>

namespace nicomo {
namespace model {

static std::string TAG("Thread");

Thread::Thread(cinamo::Logger& log, tinyxml2::XMLElement* elm)
:thread_(0xFFFFFFFF)
,ticket_(0xFFFFFFFF)
,server_time_(0xFFFFFFFF)
{
	read(log, elm);
}
Thread::Thread(cinamo::Logger& log, tinyxml2::XMLDocument* doc)
:thread_(0xFFFFFFFF)
,ticket_(0xFFFFFFFF)
,server_time_(0xFFFFFFFF)
{
	read(log, doc->RootElement());
}
Thread::Thread(cinamo::Logger& log, const std::string& filename)
:thread_(0xFFFFFFFF)
,ticket_(0xFFFFFFFF)
,server_time_(0xFFFFFFFF)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());
	read(log, doc.RootElement());
}

Thread::~Thread() {
	for(std::vector<const Comment*>::iterator it = chatList.begin();it != chatList.end();++it){
		delete *it;
	}
	decltype(chatList)().swap(chatList);
}


void Thread::read(cinamo::Logger& log,tinyxml2::XMLElement* elm)
{
	bool infoGrabbed = false;
	if(std::string("packet") != elm->Name() ){
		CINAMO_EXCEPTION(Exception, "Invalid Element Name: %s", elm->Name())
	}
	for( tinyxml2::XMLElement* ch = elm->FirstChildElement(); ch; ch = ch->NextSiblingElement() ) {
		if(std::string("thread") == ch->Name()){
			if(infoGrabbed){
				continue;
			}
			infoGrabbed |= true;
			cinamo::xml::parseAttr("thread", this->thread_, (unsigned long long)0, ch);
			cinamo::xml::parseAttr("ticket", this->ticket_, (unsigned long long)0, ch);
			cinamo::xml::parseAttr("server_time", this->server_time_, (unsigned long long)0, ch);
			if(log.t()){
				log.t(TAG, "Thread ID: %llu", this->thread());
				log.t(TAG, "Ticket: %llu", this->ticket());
				log.t(TAG, "Server Time: %llu", this->server_time());
			}
		}else if(std::string("chat") == ch->Name()){
			const Comment* com = new Comment(log, ch);
			std::vector<const Comment*>::iterator it = std::upper_bound(chatList.begin(), chatList.end(), com, Comment::CompareLessByVpos());
			chatList.insert(it, com);
		}else{
			log.w(TAG, "Unknwon element:%s(ignored)", ch->Name());
		}
	}
}

Thread::Iterator Thread::begin() const
{
	return chatList.begin();
}
Thread::Iterator Thread::end() const
{
	return chatList.end();
}

size_t Thread::size() const
{
	return chatList.size();
}

}}
