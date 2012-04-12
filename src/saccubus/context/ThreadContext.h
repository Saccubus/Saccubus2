/*
 * ThreadContext.h
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#ifndef THREADCONTEXT_H_
#define THREADCONTEXT_H_

#include <vector>
#include <tr1/memory>
#include <nekomata/system/System.h>
#include "../classdefs.h"

namespace saccubus {
namespace context {

class ThreadContext {
private:
	const meta::Thread* const origThread;
	const meta::PlayInfo* const playInfo;
	std::vector<std::tr1::shared_ptr<nekomata::system::Comment> > chatList;
	void process();
public:
	ThreadContext(const meta::Thread* const origThread, const meta::PlayInfo* playInfo);
	virtual ~ThreadContext();
public:

};

}}
#endif /* THREADCONTEXT_H_ */
