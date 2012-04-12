/*
 * Thread.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <string>
#include <libxml2/libxml/tree.h>
#include "Comment.h"
#include "../logging/Logger.h"
#include "../util/ClassAccessor.h"

namespace saccubus {
namespace meta {

/**
 * XML内でのスレッドを表現するクラス
 * ！！　イミュータブル（変更不可）　！！
 */
class Thread {
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, thread)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, ticket)
	DEF_ATTR_ACCESSOR(public, private, unsigned long long, server_time)
	std::vector<const Comment*> chatList;
public:
	typedef std::vector<const Comment*>::const_iterator Iterator;
	Thread(logging::Logger& log, xmlNode* node);
	Thread(logging::Logger& log, xmlDoc* doc);
	Thread(logging::Logger& log, const std::string& filename);
	virtual ~Thread();
private:
	void read(logging::Logger& log, xmlNode* node);
public:
	Iterator begin() const;
	Iterator end() const;
	size_t size() const;
};

}}
#endif /* THREAD_H_ */
