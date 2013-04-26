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

#include <iostream>
#include <sstream>
#include <cinamo/Logger.h>
#include "ScriptLayer.h"
#include "item/Label.h"
#include "item/Shape.h"
#include "../draw/Context.h"

namespace saccubus {
namespace layer {

const static std::string TAG("ScriptLayer");

using nekomata::system::System;

ScriptLayer::ScriptLayer(cinamo::Logger& log, NekomataSystem* nekoSystem)
:Layer(log)
,nekoSystem_(nullptr)
{
	this->nekoSystem(nekoSystem);

}

/******************************************************************************************************************
 * レイヤ
 ******************************************************************************************************************/
void ScriptLayer::resolvePos(std::shared_ptr<saccubus::draw::Context> ctx, item::NekoItem* nekoItem, float screenWidth, float screenHeight, float* x, float* y)
{
	switch(nekoItem->posX()){
	case item::NekoItem::CenterX:
		*x = (screenWidth/2)+(nekoItem->drawable()->x() * ctx->factor())-(nekoItem->width(ctx)/2);
		break;
	case item::NekoItem::Right:
		*x = screenWidth+(nekoItem->drawable()->x() * ctx->factor())-nekoItem->width(ctx);
		break;
	case item::NekoItem::Left:
		*x = nekoItem->drawable()->x() * ctx->factor();
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknown NekoItem PosX type.");
	}
	switch(nekoItem->posY()){
	case item::NekoItem::CenterY:
		*y = (screenHeight/2)+(nekoItem->drawable()->y() * ctx->factor())-(nekoItem->height(ctx)/2);
		break;
	case item::NekoItem::Top:
		*y = nekoItem->drawable()->y() * ctx->factor();
		break;
	case item::NekoItem::Bottom:
		*y = screenHeight+(nekoItem->drawable()->y() * ctx->factor())-nekoItem->height(ctx);
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknown NekoItem PosY type.");
	}
}
void ScriptLayer::draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	std::vector<nekomata::system::Drawable*> lst;
	nekoSystem()->fetchDrawables(lst);
	for(std::vector<nekomata::system::Drawable*>::const_iterator it = lst.begin(); it != lst.end(); ++it){
		nekomata::system::Drawable* const obj = *it;
		if(!obj->visible()) continue;
		item::NekoItem* const item = dynamic_cast<item::NekoItem*>(obj);
		if(!item){
			// FIXME: 仮。他のコマンドもすべて実装したら、これはNULL（dynamic_cast失敗）にはならないはず。
			continue;
		}
		float x, y;
		resolvePos(ctx, item, ctx->width(), ctx->height(), &x, &y);
		item->draw(ctx, x, y);
	}
}

bool ScriptLayer::onClick(int x, int y)
{
	return false;
}

void ScriptLayer::measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight)
{
	this->Layer::measure(w, h, measuredWidth, measuredHeight);
	this->nekoSystem()->setScreenSize(w, h);
}


}}
