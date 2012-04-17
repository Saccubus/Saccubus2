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
