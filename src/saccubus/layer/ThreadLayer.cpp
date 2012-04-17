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

#include "ThreadLayer.h"
#include "../PluginOrganizer.h"
#include "../draw/CommentFactory.h"
#include "../draw/Renderer.h"
#include "../draw/ShapeFactory.h"

namespace saccubus {
namespace layer {

ThreadLayer::ThreadLayer(logging::Logger& log, draw::Renderer* renderer, PluginOrganizer* organizer)
:Layer(log, renderer)
{
	this->commentFactory = organizer->newCommentFactory(this->renderer());
	this->shapeFactory = organizer->newShapeFactory(this->renderer());

}

ThreadLayer::~ThreadLayer() {
	delete this->nekomataLayer;
	delete this->mainCommentLayer;
	delete this->forkedCommentLayer;

	delete this->commentFactory;
	delete this->shapeFactory;
}

void ThreadLayer::draw(float vpos)
{
	//コメントの供給（破棄タイミングは各々のレイヤが決めてね）
	//描画
	this->nekomataLayer->draw(vpos);
	this->mainCommentLayer->draw(vpos);
	this->forkedCommentLayer->draw(vpos);
}


}}
