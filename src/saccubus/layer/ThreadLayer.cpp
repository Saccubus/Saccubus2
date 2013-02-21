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
#include <memory>
#include "ThreadLayer.h"
#include "item/Comment.h"
#include "../python/PyBridge.h"
#include "../model/Thread.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/Renderer.h"
#include "../draw/ShapeFactory.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(logging::Logger& log, const model::Thread& thread, const std::string& ngScript, python::PyBridge* bridge, const model::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* pluginOrganizer)
:Layer(log)
,thread(thread)
,ngScript(ngScript)
,bridge(bridge)
{
	{ // ファクトリ
		this->shapeFactory(pluginOrganizer->newShapeFactory(renderer));
		this->commentFactory(pluginOrganizer->newCommentFactory(renderer));
	}
	{ // ねこまたとの接続
		this->nekoLogger = new nekomata::logging::Logger(log.stream(), log.levelAsNekomataLogger());
		this->nekoSystem(new NekomataSystem(*this->nekoLogger, this->commentFactory(), this->shapeFactory()));
		this->neko = new nekomata::Nekomata(*(this->nekoSystem()), *this->nekoLogger);
	}

	{ // これでやっとレイヤの作成
		this->scriptLayer = new ScriptLayer(log, this->nekoSystem());
		this->forkedCommentLayer = pluginOrganizer->newCommentLayer(this, true);
		this->mainCommentLayer = pluginOrganizer->newCommentLayer(this, false);
	}

	this->nekoSystem()->tellCommentLayers(this->forkedCommentLayer, this->mainCommentLayer);

	{ /* 確定済みコメントを渡す */
		for(model::Thread::Iterator it = thread.begin(); it != thread.end(); ++it){
			if(bridge->askCommentShouldBeIgnored(this->ngScript, **it)){
				continue;
			}
			if((*it)->haveScript()){
				this->neko->queueMessage(std::shared_ptr<nekomata::system::Message>(new nekomata::system::Script((*it)->vpos(), (*it)->node())));
			}else if((*it)->fork()){
				this->forkedCommentLayer->queueComment(
						std::shared_ptr<item::Comment>(new item::Comment(commentFactory(), shapeFactory(), table, *it))
						);
			}else{
				this->mainCommentLayer->queueComment(
						std::shared_ptr<item::Comment>(new item::Comment(commentFactory(), shapeFactory(), table, *it))
						);
			}
		}
	}

}

ThreadLayer::~ThreadLayer() {

	{
		delete this->mainCommentLayer;
		this->mainCommentLayer = 0;
		delete this->forkedCommentLayer;
		this->forkedCommentLayer = 0;
	}

	{ // ファクトリ
		delete this->commentFactory();
		this->commentFactory(0);
		delete this->shapeFactory();
		this->shapeFactory(0);
	}

	{ // ねこまたと接続解除
		delete this->neko;
		this->neko = 0;
		delete this->scriptLayer;
		this->scriptLayer = 0;
		delete this->nekoSystem();
		this->nekoSystem(0);
		delete this->nekoLogger;
		this->nekoLogger = 0;
	}
}

void ThreadLayer::draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos)
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

#define updateWidth(target) do { \
	int mesW = *measuredWidth;\
	int mesH = *measuredHeight;\
	target->measure(w, h, &mesW, &mesW);\
	*measuredWidth = std::max(mesW, *measuredWidth);\
	*measuredHeight = std::max(mesH, *measuredHeight);\
} while(0)

void ThreadLayer::measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight)
{
	*measuredWidth = w;
	*measuredHeight = h;
	updateWidth(this->scriptLayer);
	updateWidth(this->mainCommentLayer);
	updateWidth(this->forkedCommentLayer);
}

}}
