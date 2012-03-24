/*
 * Thread.cpp
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#include <libxml2/libxml/parser.h>
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
	// TODO Auto-generated destructor stub
}

void Thread::read(logging::Logger& log, xmlNode* node)
{
	bool infoGrabbed = false;
	if(xmlStrcmp(node->name, reinterpret_cast<const unsigned char*>("packet")) != 0){
		throw logging::Exception("Invalid Element Name: %s", node->name);
	}
	for(xmlNode* child = node->children;child;child = child->next){
		if(xmlStrcmp(child->name, reinterpret_cast<const unsigned char*>("thread")) == 0){
			if(infoGrabbed){
				continue;
			}
			infoGrabbed |= true;
			this->thread(readNodeProp(node, "thread", (unsigned long long)0));
			this->ticket(readNodeProp(node, "ticket", (unsigned long long)0));
			this->server_time(readNodeProp(node, "server_time", (unsigned long long)0));
			if(log.t()){
				log.t(TAG, "Thread ID: %llu", this->thread());
				log.t(TAG, "Ticket: %llu", this->ticket());
				log.t(TAG, "Server Time: %llu", this->server_time());
			}
		}else if(xmlStrcmp(child->name, reinterpret_cast<const unsigned char*>("chat")) == 0){
			chatList.push_back(Chat(log, child));
		}else{
			if(log.t()){
				log.t(TAG, "Unknwon element: %s(ignored)", child->name);
			}
		}
	}
}

}}
