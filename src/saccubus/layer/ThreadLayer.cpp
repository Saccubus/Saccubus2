/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <memory>
#include <algorithm>
#include <cinamo/Logger.h>
#include <nicomo/model/Thread.h>

#include "ThreadLayer.h"
#include "item/Comment.h"
#include "../python/PyBridge.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/Renderer.h"
#include "../draw/ShapeFactory.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(cinamo::Logger& log, const nicomo::model::Thread& thread, const std::string& ngScript, python::PyBridge* bridge, const nicomo::model::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* pluginOrganizer)
:Layer(log)
,commentFactory_(nullptr)
,shapeFactory_(nullptr)
,nekoSystem_(nullptr)
,thread(thread)
,ngScript(ngScript)
,bridge(bridge)
,scriptLayer(nullptr)
,localCommentLayer(nullptr)
,mainCommentLayer(nullptr)
,forkedCommentLayer(nullptr)

{
	{ // ファクトリ
		this->shapeFactory(pluginOrganizer->newShapeFactory(renderer));
		this->commentFactory(pluginOrganizer->newCommentFactory(renderer));
	}
	{ // ねこまたとの接続
		this->nekoLogger = new nekomata::logging::Logger(log);
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
		for(nicomo::model::Thread::Iterator it = thread.begin(); it != thread.end(); ++it){
			const nicomo::model::Comment* const obj = *it;
			if(bridge->askCommentShouldBeIgnored(this->ngScript, *obj)){
				continue;
			}
			std::shared_ptr<item::Comment> com(new item::Comment(commentFactory(), shapeFactory(), table, obj));
			if(com->haveScript()){
				this->neko->queueMessage(std::shared_ptr<nekomata::system::Message>(new nekomata::system::Script(obj->vpos(), com->node())));
			}else if(obj->fork()){
				this->forkedCommentLayer->queueComment(com);
			}else{
				this->mainCommentLayer->queueComment(com);
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
