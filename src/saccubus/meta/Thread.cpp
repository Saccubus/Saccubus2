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

#include <libxml2/libxml/parser.h>
#include <algorithm>
#include "../logging/Exception.h"
#include "Util.h"
#include "Thread.h"

namespace saccubus {
namespace meta {

static std::string TAG("Thread");

Thread::Thread(logging::Logger& log, xmlNode* node)
{
	read(log, node);
}
Thread::Thread(logging::Logger& log, xmlDoc* doc)
{
	xmlNode* root = xmlDocGetRootElement(doc);
	read(log, root);
}
Thread::Thread(logging::Logger& log, const std::string& filename)
{
	xmlDoc* doc = xmlReadFile(filename.c_str(), NULL, 0);
	xmlNode* root = xmlDocGetRootElement(doc);
	read(log, root);
	xmlFreeDoc(doc);
}

Thread::~Thread() {
	for(std::vector<const Comment*>::iterator it = chatList.begin();it != chatList.end();++it){
		delete *it;
	}
}


void Thread::read(logging::Logger& log, xmlNode* node)
{
	bool infoGrabbed = false;
	if(!compareNodeName(node, "packet")){
		throw logging::Exception("Invalid Element Name: %s", node->name);
	}
	for(xmlNode* child = node->children;child;child = child->next){
		if(compareNodeName(child, "thread")){
			if(infoGrabbed){
				continue;
			}
			infoGrabbed |= true;
			this->thread(readNodeProp(child, "thread", (unsigned long long)0));
			this->ticket(readNodeProp(child, "ticket", (unsigned long long)0));
			this->server_time(readNodeProp(child, "server_time", (unsigned long long)0));
			if(log.t()){
				log.t(TAG, "Thread ID: %llu", this->thread());
				log.t(TAG, "Ticket: %llu", this->ticket());
				log.t(TAG, "Server Time: %llu", this->server_time());
			}
		}else if(compareNodeName(child, "chat")){
			const Comment* com = new Comment(log, child);
			std::vector<const Comment*>::iterator it = std::upper_bound(chatList.begin(), chatList.end(), com, Comment::comparareLessByVpos);
			chatList.insert(it, com);
		}else{
			if(log.t()){
				log.t(TAG, "Unknwon element: %s(ignored)", child->name);
			}
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
