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

#include <sstream>
#include "Comment.h"
#include "Util.h"

namespace saccubus {
namespace meta {

static std::string TAG("Comment");

Comment::Comment(logging::Logger& log, xmlNode* node) {
	this->thread(readNodeProp(node, "thread", (unsigned long long)0));
	this->no(readNodeProp(node, "no", (unsigned long long)0));
	this->vpos(readNodeProp(node, "vpos", (float)0)/100);
	this->date(readNodeProp(node, "date", (unsigned long long)0));
	this->deleted(readNodeProp(node, "deleted", (unsigned long long)0));
	this->score(readNodeProp(node, "score", (long long)0));
	this->user_id(readNodeProp(node, "user_id", ""));
	this->anonymity(readNodeProp(node, "anonymity", true));
	this->leaf(readNodeProp(node, "leaf", false));
	this->premium(readNodeProp(node, "premium", false));
	this->fork(readNodeProp(node, "fork", false));
	this->mail(readNodeProp(node, "mail", ""));
	this->message(readNodeContent(node));

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
				this->message().c_str()
				);
	}
}

Comment::Comment()
{
	this->thread(0LLU);
	this->no(0LLU);
	this->vpos(-1);
	this->date(0LLU);
	this->deleted(0LLU);
	this->score(0);
	this->user_id("");
	this->mail("");
	this->message("");
	this->anonymity(false);
	this->leaf(false);
	this->premium(false);
	this->fork(false);
}

void Comment::splitMail()
{
	this->mailList.clear();
	std::istringstream ss(this->mail());
	std::string mailopt;
	while(std::getline(ss, mailopt, ' ')){
		this->mailList.push_back(mailopt);
	}
}

Comment::~Comment() {
}

std::string Comment::mail() const
{
	return _mail;
}
void Comment::mail(std::string const& mail)
{
	this->_mail = mail;
	this->splitMail();
}

size_t Comment::mailSize() const
{
	return mailList.size();
}
Comment::MailIterator Comment::mailBegin() const
{
	return mailList.begin();
}
Comment::MailIterator Comment::mailEnd() const
{
	return mailList.end();
}

bool Comment::comparareLessByVpos(const Comment* a, const Comment* b){
	return a->vpos() < b->vpos();
}

}}
