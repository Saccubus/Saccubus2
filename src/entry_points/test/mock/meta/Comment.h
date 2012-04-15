/*
 * Comment.h
 *
 *  Created on: 2012/04/15
 *      Author: psi
 */

#ifndef MOCK_META_COMMENT_H_
#define MOCK_META_COMMENT_H_

#include "../../TestCommon.h"
#include "../../../../saccubus/meta/Comment.h"

namespace saccubus {
namespace mock {
namespace meta {

class Comment: public saccubus::meta::Comment {
public:
	Comment();
	virtual ~Comment();
public:
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, thread);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, no);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, float, vpos);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, date);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, unsigned long long, deleted);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, long long, score);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, std::string, user_id);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, std::string, mail);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, std::string, message);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, anonymity);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, leaf);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, premium);
	MOCK_ACCESSOR_EXPAND(saccubus::meta::Comment, bool, fork);
};

}}}
#endif /* MOCK_META_COMMENT_H_ */
