/*
 * ThreadContext.h
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#ifndef CONTEXT_THREAD_H_
#define CONTEXT_THREAD_H_

#include <vector>
#include <nekomata/system/System.h>
#include "../classdefs.h"

namespace saccubus {
namespace context {

class Thread {
private:
	python::PyBridge* const bridge;
	const meta::Thread* const origThread;
	const meta::PlayInfo* const playInfo;
	std::vector<const nekomata::system::Comment*> commentList;
	void process();
public:
	Thread(python::PyBridge* const bridge, const meta::Thread* const origThread, const meta::PlayInfo* playInfo);
	virtual ~Thread();
public:
	typedef std::vector<const nekomata::system::Comment*>::const_iterator CommentIterator;
	CommentIterator commentBegin();
	CommentIterator commentEnd();
	std::size_t commentSize();
};

}}
#endif /* CONTEXT_THREAD_H_ */
