/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <sstream>
#include <cinamo/String.h>
#include <cinamo/Logger.h>
#include "Comment.h"
#include "../NekomataSystem.h"

namespace saccubus {
namespace layer {
namespace item {

struct Comment::NekomataReplaceOperation
{
public:
	static void apply(nekomata::system::Replace* replace, Comment* comment);
	static void apply(nekomata::system::System* system, Comment* comment);
};

void Comment::NekomataReplaceOperation::apply(nekomata::system::System* system, Comment* comment)
{
	for(nekomata::system::System::ReplaceIterator it = system->replaceBegin(); it != system->replaceEnd(); ++it){
		NekomataReplaceOperation::apply(*it, comment);
	}
}

void Comment::NekomataReplaceOperation::apply(nekomata::system::Replace* replace, Comment* comment)
{
	if(!replace->enabled()) return;
	if(replace->src().size() > 0 && comment->message().find(replace->src()) == std::string::npos){
		return; //マッチしなかった。
	}

	std::vector<std::string> targets(cinamo::splitSpace(replace->target()));
	if(targets.size() > 0){
		for(std::vector<std::string>::const_iterator it = targets.begin(); it != targets.end(); ++it){
			if(
				( *it == "owner" && comment->layer() == item::Comment::Forked ) ||
				( *it == "user" && comment->layer() == item::Comment::Normal )
			){
				break;
			}
		}
		return; //ターゲットじゃない。
	}

	//色やポジションが設定される。
	if(nekomata::system::Replace::SAME_COLOR != replace->color()) comment->color(replace->color());
	if(replace->size().size() > 0) comment->applyMail(replace->size());
	if(replace->pos().size() > 0) comment->applyMail(replace->pos());

	if(replace->dest().size() <= 0){
		return; //メッセージの書き換えは行わない。
	}

	if(!replace->partial()){ //完全一致
		if(replace->src() == comment->message()){
			comment->message(replace->dest());
		}
	}else{
		if(replace->fill()){
			if(comment->message().find(replace->src()) != std::string::npos){
				comment->message(replace->dest());
			}
		}else{
			std::vector<std::string> lst(cinamo::split(comment->message(), replace->src()));
			std::stringstream ss;
			for(std::vector<std::string>::const_iterator it = lst.begin(); it != lst.end(); ++it){
				if(ss.tellg() > 0){
					ss << replace->dest();
				}
				ss << *it;
			}
			comment->message(ss.str());
		}
	}
}

void Comment::onDeploy(nekomata::system::System* system)
{
	nekomata::system::System::ReplaceIterator it = system->replaceBegin();
	for(; it != system->replaceEnd(); ++it){
		NekomataReplaceOperation::apply(*it, this);
	}
	system->queueMessage(this->createNekomataMessage());
}

}}}


