/*
 * VideoContext.cpp
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#include "VideoContext.h"
#include "../meta/Video.h"
#include "../meta/Thread.h"
#include "ThreadContext.h"

namespace saccubus {
namespace context {

VideoContext::VideoContext(python::PyBridge* const bridge, const meta::Video* const video)
:bridge(bridge), video(video){
	for(meta::Video::ThreadIterator it = video->threadBegin(); it != video->threadEnd(); ++it){
		const meta::Thread* const thread = it->second;

		ThreadContext* const threadContext = new ThreadContext(bridge, thread, video->playInfo());
		this->threads.push_back(threadContext);
	}

}

VideoContext::~VideoContext() {
	for(std::vector<ThreadContext*>::iterator it = threads.begin(); it != threads.end(); ++it){
		delete *it;
	}
}

VideoContext::ThreadIterator VideoContext::threadBegin() const
{
	return this->threads.begin();
}
VideoContext::ThreadIterator VideoContext::threadEnd() const
{
	return this->threads.end();
}
std::size_t VideoContext::threadSize() const
{
	return this->threads.size();
}

}}

