/*
 * Chat.cpp
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#include <sstream>
#include "../logging/Exception.h"
#include "Chat.h"
#include "Util.h"

namespace saccubus {
namespace meta {

static std::string TAG("Chat");

Chat::Chat(logging::Logger& log, xmlNode* node) {
	this->thread(readNodeProp(node, "thread", (unsigned long long)0));
	this->no(readNodeProp(node, "no", (unsigned long long)0));
	this->vpos(readNodeProp(node, "vpos", (float)0)/100);
	this->date(readNodeProp(node, "date", (unsigned long long)0));
	this->deleted(readNodeProp(node, "deleted", (unsigned long long)0));
	this->score(readNodeProp(node, "score", (unsigned long long)0));
	this->user_id(readNodeProp(node, "user_id", ""));
	this->anonymity(readNodeProp(node, "anonymity", true));
	this->leaf(readNodeProp(node, "leaf", false));
	this->premium(readNodeProp(node, "premium", false));
	this->fork(readNodeProp(node, "fork", false));
	std::istringstream ss(readNodeProp(node, "mail", ""));
	std::string mailopt;
	while(std::getline(ss, mailopt, ' ')){
		this->mail.push_back(mailopt);
	}

	xmlChar* content = xmlNodeGetContent(node);
	if(!content){
		throw logging::Exception("Invalid XML. Content for chat not found.");
	}
	this->body(reinterpret_cast<char*>(content));
	xmlFree(content);

	if(log.t()){
		log.t(TAG, "Thread: %llu No:%llu vpos:%f Date:%llu Deleted:%llu Score:%llu UserId:%s Anon:%d Leaf:%d Premium:%d Fork:%d -> %s",
				this->thread(),
				this->no(),
				this->vpos(),
				this->date(),
				this->deleted(),
				this->score(),
				this->user_id().c_str(),
				this->anonymity(),
				this->leaf(),
				this->premium(),
				this->fork(),
				this->body().c_str()
				);
	}
}

Chat::~Chat() {
}

}}
