/*
 * VideoContext.cpp
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#include "Video.h"
#include "Thread.h"
#include "../meta/Video.h"
#include "../meta/Thread.h"

namespace saccubus {
namespace context {

Video::Video(python::PyBridge* const bridge, const meta::Video* const video)
:bridge(bridge), video(video){
	for(meta::Video::ThreadIterator it = video->threadBegin(); it != video->threadEnd(); ++it){
		const meta::Thread* const thread = it->second;

		Thread* const threadContext = new Thread(bridge, thread, video->playInfo());
		this->threads.push_back(threadContext);
	}

}

Video::~Video() {
	for(std::vector<Thread*>::iterator it = threads.begin(); it != threads.end(); ++it){
		delete *it;
	}
}

Video::ThreadIterator Video::threadBegin() const
{
	return this->threads.begin();
}
Video::ThreadIterator Video::threadEnd() const
{
	return this->threads.end();
}
std::size_t Video::threadSize() const
{
	return this->threads.size();
}

}}

