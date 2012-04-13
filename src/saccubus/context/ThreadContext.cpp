/*
 * ThreadContext.cpp
 *
 *  Created on: 2012/04/12
 *      Author: psi
 */

#include <algorithm>
#include "ThreadContext.h"
#include "../meta/Thread.h"
#include "../meta/PlayInfo.h"
#include "../meta/ReplaceTable.h"
#include "../util/StringUtil.h"

namespace saccubus {
namespace context {

ThreadContext::ThreadContext(python::PyBridge* const bridge, const meta::Thread* const origThread, const meta::PlayInfo* playInfo)
:bridge(bridge), origThread(origThread), playInfo(playInfo)
{
	this->process();
}

ThreadContext::~ThreadContext() {
	for(std::vector<const nekomata::system::Comment*>::iterator it=commentList.begin();it != commentList.end(); ++it){
		delete *it;
	}
}

static bool order(const nekomata::system::Comment* const a, const nekomata::system::Comment* const b)
{
	return a->vpos() < b->vpos();
}

void ThreadContext::process()
{
	for(meta::Thread::Iterator it = origThread->begin(); it != origThread->end(); ++it){
		const meta::Comment* const origCom = *it;
		nekomata::system::Comment* const com(new nekomata::system::Comment(
				playInfo->replaceTable()->replace(origCom->message()),
				origCom->vpos(),
				origCom->user_id() == util::format("%lld", playInfo->user_id()),
				origCom->mail(),
				false,
				origCom->premium(),
				0,//origCom->color();
				0.0,
				origCom->no()
		));
		std::vector<const nekomata::system::Comment*>::iterator insertPoint = std::upper_bound(commentList.begin(), commentList.end(), com, order);
		commentList.insert(insertPoint, com);
	}
}

ThreadContext::CommentIterator ThreadContext::commentBegin()
{
	return commentList.begin();
}
ThreadContext::CommentIterator ThreadContext::commentEnd()
{
	return commentList.end();
}
std::size_t ThreadContext::commentSize()
{
	return commentList.size();
}

}}
