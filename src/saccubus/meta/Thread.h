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

class Thread {
	DEF_ATTR_ACCESSOR(public, public, unsigned long long, thread)
	DEF_ATTR_ACCESSOR(public, public, unsigned long long, ticket)
	DEF_ATTR_ACCESSOR(public, public, unsigned long long, server_time)
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
	Iterator begin();
	Iterator end();
	size_t size();
};

}}
#endif /* THREAD_H_ */
