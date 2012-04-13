/*
 * ThreadContext.h
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#ifndef THREADCONTEXT_H_
#define THREADCONTEXT_H_

#include <vector>
#include <nekomata/system/System.h>
#include "../classdefs.h"

namespace saccubus {
namespace context {

class ThreadContext {
private:
	python::PyBridge* const bridge;
	const meta::Thread* const origThread;
	const meta::PlayInfo* const playInfo;
	std::vector<const nekomata::system::Comment*> commentList;
	void process();
public:
	ThreadContext(python::PyBridge* const bridge, const meta::Thread* const origThread, const meta::PlayInfo* playInfo);
	virtual ~ThreadContext();
public:
	typedef std::vector<const nekomata::system::Comment*>::const_iterator CommentIterator;
	CommentIterator commentBegin();
	CommentIterator commentEnd();
	std::size_t commentSize();
};

}}
#endif /* THREADCONTEXT_H_ */
