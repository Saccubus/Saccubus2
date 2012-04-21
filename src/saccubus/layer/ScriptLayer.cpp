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
void ScriptLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{
	const float centerX = ctx->width()/2;
	const float centerY = ctx->height()/2;
	for(NekomataSystem::LabelIterator it = nekoSystem()->labelBegin(); it != nekoSystem()->labelEnd(); ++it){
		item::Label* label = dynamic_cast<item::Label*>(*it);
		if(!label->visible()) continue;
		draw::Sprite::Handler<draw::Sprite> spr = label->querySprite(ctx);
		spr->draw(ctx, label->x(), label->y());
	}
}

bool ScriptLayer::onClick(int x, int y)
{
	return false;
}


}}
