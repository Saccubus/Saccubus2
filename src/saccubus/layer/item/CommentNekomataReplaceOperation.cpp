/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "Comment.h"
#include "../../logging/Logger.h"
#include "../../util/StringUtil.h"
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

	std::vector<std::string> targets;
	util::splitSpace(replace->target(), targets);
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
			std::vector<std::string> lst;
			util::split(comment->message(), replace->src(), lst);
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


