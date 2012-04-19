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

#include <algorithm>
#include "ThreadLayer.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/Renderer.h"
#include "../draw/ShapeFactory.h"
#include "item/CommentPipeLine.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(logging::Logger& log, const meta::Thread& thread, meta::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* organizer)
:Layer(log)
,thread(thread)
{
	{ // ねこまたとの接続
		this->nekoLogger = new nekomata::logging::Logger(log.stream(), log.levelAsNekomataLogger());
		this->nekomataLayer = new NekomataLayer(log, *this->nekoLogger);
		this->nekomata = new nekomata::Nekomata(*this->nekomataLayer, *this->nekoLogger);
	}

	{ // ファクトリ
		this->shapeFactory(organizer->newShapeFactory(renderer));
		this->commentFactory(organizer->newCommentFactory(renderer));
		this->pipeLine(new item::CommentPipeLine(log, table, this->nekomataLayer));
	}

	{ // コメントレイヤをプラグインオーガナイザからもらってくる

	}


}

ThreadLayer::~ThreadLayer() {

	{
		delete this->mainCommentLayer;
		delete this->forkedCommentLayer;
	}

	{ // ファクトリ
		delete this->pipeLine();
		this->pipeLine(0);
		delete this->commentFactory();
		this->commentFactory(0);
		delete this->shapeFactory();
		this->shapeFactory(0);
	}

	{ // ねこまたと接続解除
		delete this->nekomata;
		delete this->nekomataLayer;
		delete this->nekoLogger;
	}
}

void ThreadLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	this->nekomataLayer->draw(ctx, vpos);
	this->mainCommentLayer->draw(ctx, vpos);
	this->forkedCommentLayer->draw(ctx, vpos);
}

void ThreadLayer::getCommentBetween(float from, float to, bool isForked, std::vector<const meta::Comment*>& result) const
{
	meta::Comment::CompareLessByVpos cmp;
	meta::Thread::Iterator it = std::lower_bound(thread.begin(), thread.end(), from, cmp);
	meta::Thread::Iterator const end = std::upper_bound(thread.begin(), thread.end(), to, cmp);

	for(; it != end; ++it){
		if((*it)->fork() == isForked){
			result.push_back(*it);
		}
	}
}

}}
