/*
 * Chat.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef META_COMMENT_H_
#define META_COMMENT_H_

#include <string>
#include <vector>
#include <libxml2/libxml/tree.h>
#include "../logging/Logger.h"
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace meta {

/**
 * XML内のコメントを表現するクラス。
 * ！！　イミュータブル（変更不可）　！！
 */
class Comment {
	DEF_ATTR_ACCESSOR(public, protected, unsigned long long, thread)
	DEF_ATTR_ACCESSOR(public, protected, unsigned long long, no)
	DEF_ATTR_ACCESSOR(public, protected, float, vpos)
	DEF_ATTR_ACCESSOR(public, protected, unsigned long long, date)
	DEF_ATTR_ACCESSOR(public, protected, unsigned long long, deleted)
	DEF_ATTR_ACCESSOR(public, protected, long long, score)
	DEF_ATTR_ACCESSOR(public, protected, std::string, user_id)
	DEF_ATTR_ACCESSOR(public, protected, std::string, message)
	DEF_ATTR_ACCESSOR(public, protected, bool, anonymity)
	DEF_ATTR_ACCESSOR(public, protected, bool, leaf)
	DEF_ATTR_ACCESSOR(public, protected, bool, premium)
	DEF_ATTR_ACCESSOR(public, protected, bool, fork)
public: /* mailだけは少しだけ扱いが違う */
	std::string mail() const;
protected:
	void mail(std::string const& mail);
private:
	std::vector<std::string> mailList;
	std::string _mail;
protected:
	Comment();
	void splitMail();
public:
	Comment(logging::Logger& log, xmlNode* node);
	virtual ~Comment();
public:
	typedef std::vector<std::string>::const_iterator MailIterator;
	size_t mailSize() const;
	MailIterator mailBegin() const;
	MailIterator mailEnd() const;
public:
	static bool comparareLessByVpos(const Comment* a, const Comment* b);
};

}}
#endif /* META_COMMENT_H_ */
