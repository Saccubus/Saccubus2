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

ThreadContext::ThreadContext(const meta::Thread* const origThread, const meta::PlayInfo* playInfo)
:origThread(origThread), playInfo(playInfo)
{
	this->process();
}

ThreadContext::~ThreadContext() {
	// TODO Auto-generated destructor stub
}

static bool order(const std::tr1::shared_ptr<nekomata::system::Comment> a, const std::tr1::shared_ptr<nekomata::system::Comment> b)
{
	return a->vpos() < b->vpos();
}

void ThreadContext::process()
{
	for(meta::Thread::Iterator it = origThread->begin(); it != origThread->end(); ++it){
		const meta::Comment* const origCom = *it;
		std::tr1::shared_ptr<nekomata::system::Comment> com(new nekomata::system::Comment(
				playInfo->replaceTable()->replace(origCom->message()),
				origCom->vpos(),
				origCom->user_id() == util::format("%d", playInfo->user_id()),
				origCom->mail(),
				false,
				origCom->premium(),
				0,//origCom->color();
				0.0,
				origCom->no()
		));
		std::vector<std::tr1::shared_ptr<nekomata::system::Comment> >::iterator insertPoint = std::upper_bound(chatList.begin(), chatList.end(), com, order);
		chatList.insert(insertPoint, com);
	}
}

}}
