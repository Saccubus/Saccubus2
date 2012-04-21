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
void ScriptLayer::resolvePos(item::NekoItem* nekoItem, float width, float height, float* x, float* y)
{
	switch(nekoItem->posX()){
	case item::NekoItem::CenterX:
		*x = (width/2)+nekoItem->drawable()->x();
		break;
	case item::NekoItem::Right:
		*x = width+nekoItem->drawable()->x();
		break;
	case item::NekoItem::Left:
		*x = nekoItem->drawable()->x();
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknown NekoItem PosX type.");
	}
	switch(nekoItem->posY()){
	case item::NekoItem::CenterY:
		*y = (height/2)+nekoItem->drawable()->y();
		break;
	case item::NekoItem::Top:
		*y = nekoItem->drawable()->y();
		break;
	case item::NekoItem::Bottom:
		*y = height+nekoItem->drawable()->y();
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknown NekoItem PosY type.");
	}
}
void ScriptLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	for(NekomataSystem::LabelIterator it = nekoSystem()->labelBegin(); it != nekoSystem()->labelEnd(); ++it){
		item::Label* label = dynamic_cast<item::Label*>(*it);
		if(!label->visible()) continue;
		draw::Sprite::Handler<draw::Sprite> spr = label->querySprite(ctx);
		float x,y;
		resolvePos(label, ctx->width(), ctx->height(), &x, &y);
		spr->draw(ctx, x, y);
	}
	for(NekomataSystem::ShapeIterator it = nekoSystem()->shapeBegin(); it != nekoSystem()->shapeEnd(); ++it){
		item::Shape* shape = dynamic_cast<item::Shape*>(*it);
		if(!shape->visible()) continue;
		draw::Sprite::Handler<draw::Sprite> spr = shape->querySprite(ctx);
		float x,y;
		resolvePos(shape, ctx->width(), ctx->height(), &x, &y);
		spr->draw(ctx, x, y);
	}
}

bool ScriptLayer::onClick(int x, int y)
{
	return false;
}


}}
