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

#ifndef THREADLAYER_H_
#define THREADLAYER_H_

#include <vector>
#include "../classdefs.h"
#include "CommentLayer.h"
#include "NekomataLayer.h"

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
private:
	const meta::Thread& thread;
private:
	draw::CommentFactory* commentFactory;
	draw::ShapeFactory* shapeFactory;
private:
	item::CommentPipeLine* commentPipeLine;
private:
	NekomataLayer* nekomataLayer;
	CommentLayer* mainCommentLayer;
	CommentLayer* forkedCommentLayer;
public:
	ThreadLayer(logging::Logger& log, const meta::Thread& thread, meta::ReplaceTable* table, draw::Renderer* renderer, PluginOrganizer* organizer);
	virtual ~ThreadLayer();
public: /* コメントレイヤから呼ばれる */
	void getCommentBetween(float from, float to, CommentLayer* self) const;
public:
	virtual void draw(float vpos);
};

}}
#endif /* THREADLAYER_H_ */
