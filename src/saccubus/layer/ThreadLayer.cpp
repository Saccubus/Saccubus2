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
#include <tr1/memory>
#include "ThreadLayer.h"
#include "../meta/Thread.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/Renderer.h"
#include "../draw/ShapeFactory.h"
#include "MessageOrganizer.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(logging::Logger& log, const meta::Thread& thread, const meta::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* pluginOrganizer)
:Layer(log)
,thread(thread)
{
	{ // ファクトリ
		this->shapeFactory(pluginOrganizer->newShapeFactory(renderer));
		this->commentFactory(pluginOrganizer->newCommentFactory(renderer));
	}
	{ // ねこまたとの接続
		this->nekoLogger = new nekomata::logging::Logger(log.stream(), log.levelAsNekomataLogger());
		this->nekoSystem = new NekomataSystem(*this->nekoLogger, this->commentFactory(), this->shapeFactory());
		this->neko = new nekomata::Nekomata(*this->nekoSystem, *this->nekoLogger);
	}

	//コメントの変換用
	this->messageOrganizer = new MessageOrganizer(log, this->commentFactory(), this->shapeFactory(), table, this->neko, this->nekoSystem);

	{ // これでやっとレイヤの作成
		this->scriptLayer = new ScriptLayer(log, this->nekoSystem);
		this->forkedCommentLayer = pluginOrganizer->newCommentLayer(true, this->messageOrganizer);
		this->mainCommentLayer = pluginOrganizer->newCommentLayer(false, this->messageOrganizer);
	}

	{ /* 確定済みコメントを渡す */
		for(meta::Thread::Iterator it = thread.begin(); it != thread.end(); ++it){
			if((*it)->haveScript()){
				this->neko->queueMessage(std::tr1::shared_ptr<nekomata::system::Message>(new nekomata::system::Script((*it)->vpos(), (*it)->node())));
			}else if((*it)->fork()){
				this->forkedCommentLayer->queueComment(*it);
			}else{
				this->mainCommentLayer->queueComment(*it);
			}
		}
	}

}

ThreadLayer::~ThreadLayer() {

	{
		delete this->mainCommentLayer;
		delete this->forkedCommentLayer;
	}

	{ // ファクトリ
		delete this->messageOrganizer;
		this->messageOrganizer = 0;
		delete this->commentFactory();
		this->commentFactory(0);
		delete this->shapeFactory();
		this->shapeFactory(0);
	}

	{ // ねこまたと接続解除
		delete this->neko;
		delete this->scriptLayer;
		delete this->nekoSystem;
		delete this->nekoLogger;
	}
}

void ThreadLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	this->neko->seek(vpos);
	this->scriptLayer->draw(ctx, vpos);
	this->mainCommentLayer->draw(ctx, vpos);
	this->forkedCommentLayer->draw(ctx, vpos);
}

bool ThreadLayer::onClick(int x, int y)
{
	if(this->forkedCommentLayer->onClick(x,y)) return true;
	if(this->mainCommentLayer->onClick(x,y)) return true;
	if(this->scriptLayer->onClick(x,y)) return true;
	return false;
}

}}
