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
#pragma once
#include <vector>
#include <nekomata/Nekomata.h>
#include <nicomo/Model.h>
#include "../classdefs.h"
#include "NekomataSystem.h"
#include "CommentLayer.h"
#include "ScriptLayer.h"

namespace saccubus {
namespace layer {
namespace item {
class CommentPipeLine;
}

/**
 * スレッド1つ分のレイヤ
 * 複数のコメントレイヤと、猫又レイヤを持つ。
 */
class ThreadLayer : public Layer {
	DEFINE_MEMBER(public, private, draw::CommentFactory*, commentFactory);
	DEFINE_MEMBER(public, private, draw::ShapeFactory*, shapeFactory);
	DEFINE_MEMBER(public, private, NekomataSystem*, nekoSystem);
private:
	const nicomo::model::Thread& thread;
	const std::string ngScript;
	python::PyBridge* bridge;
private:
	nekomata::logging::Logger* nekoLogger;
	nekomata::Nekomata* neko;
private:
	ScriptLayer* scriptLayer;
	CommentLayer* localCommentLayer;
	CommentLayer* mainCommentLayer;
	CommentLayer* forkedCommentLayer;
public:
	ThreadLayer(cinamo::Logger& log, const nicomo::model::Thread& thread, const std::string& ngScript, python::PyBridge* bridge, const nicomo::model::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* organizer);
	virtual ~ThreadLayer();
public:
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
	virtual void measure(int const w, int const h, int* const measuredWidth, int* const measuredHeight);
};

}}
