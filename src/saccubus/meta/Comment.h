/*
 * Chat.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef CHAT_H_
#define CHAT_H_

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
private:
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, thread)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, no)
	DEF_ATTR_ACCESSOR(public, private, float, vpos)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, date)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, deleted)
	DEF_ATTR_ACCESSOR(public, private, long long, score)
	DEF_ATTR_ACCESSOR(public, private, std::string, user_id)
	std::vector<std::string> mail;
	DEF_ATTR_ACCESSOR(public, private, std::string, message)
	DEF_ATTR_ACCESSOR(public, private, bool, anonymity)
	DEF_ATTR_ACCESSOR(public, private, bool, leaf)
	DEF_ATTR_ACCESSOR(public, private, bool, premium)
	DEF_ATTR_ACCESSOR(public, private, bool, fork)
public:
	Comment(logging::Logger& log, xmlNode* node);
	virtual ~Comment();
public:
	size_t mailSize() const;
	std::vector<std::string>::const_iterator mailBegin() const;
	std::vector<std::string>::const_iterator mailEnd() const;
public:
	static bool comparareLessByVpos(const Comment* a, const Comment* b);
};

}}
#endif /* CHAT_H_ */
