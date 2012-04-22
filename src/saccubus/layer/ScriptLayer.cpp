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

#include "ScriptLayer.h"
#include "../logging/Logger.h"
#include <iostream>
#include <sstream>
#include "../util/StringUtil.h"
#include "item/Label.h"
#include "item/Shape.h"
#include "../draw/Context.h"

namespace saccubus {
namespace layer {

const static std::string TAG("ScriptLayer");

using nekomata::system::System;

ScriptLayer::ScriptLayer(logging::Logger& log, NekomataSystem* nekoSystem)
:Layer(log)
{
	this->nekoSystem(nekoSystem);

}

ScriptLayer::~ScriptLayer() {
}



/******************************************************************************************************************
 * レイヤ
 ******************************************************************************************************************/
void ScriptLayer::resolvePos(item::NekoItem* nekoItem, float width, float height, float screenWidth, float screenHeight, float* x, float* y)
{
	switch(nekoItem->posX()){
	case item::NekoItem::CenterX:
		*x = (screenWidth/2)+nekoItem->drawable()->x()-(width/2);
		break;
	case item::NekoItem::Right:
		*x = screenWidth+nekoItem->drawable()->x()-width;
		break;
	case item::NekoItem::Left:
		*x = nekoItem->drawable()->x();
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknown NekoItem PosX type.");
	}
	switch(nekoItem->posY()){
	case item::NekoItem::CenterY:
		*y = (screenHeight/2)+nekoItem->drawable()->y()-(height/2);
		break;
	case item::NekoItem::Top:
		*y = nekoItem->drawable()->y();
		break;
	case item::NekoItem::Bottom:
		*y = screenHeight+nekoItem->drawable()->y()-height;
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknown NekoItem PosY type.");
	}
}
void ScriptLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	std::vector<nekomata::system::Drawable*> lst;
	nekoSystem()->fetchDrawables(lst);
	for(std::vector<nekomata::system::Drawable*>::const_iterator it = lst.begin(); it != lst.end(); ++it){
		if(!(*it)->visible()) continue;
		item::NekoItem* item = dynamic_cast<item::NekoItem*>(*it);
		draw::Sprite::Handler<draw::Sprite> spr = item->querySprite(ctx);
		float x,y;
		resolvePos(item, spr->width(), spr->height(), ctx->width(), ctx->height(), &x, &y);
		spr->draw(ctx, x, y);
	}
}

bool ScriptLayer::onClick(int x, int y)
{
	return false;
}


}}
