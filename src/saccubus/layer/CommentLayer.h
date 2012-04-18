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

#ifndef COMMENTLAYER_H_
#define COMMENTLAYER_H_

#include <deque>
#include "Layer.h"
#include <tr1/memory>
#include "../util/ClassAccessor.h"
#include "../meta/Thread.h"

namespace saccubus {
namespace layer {

class CommentLayer: public saccubus::layer::Layer {
	DEF_ATTR_ACCESSOR(public, private, bool, isForked);
private:
	ThreadLayer* const threadLayer;
public:
	CommentLayer(logging::Logger& log, draw::Renderer* renderer, ThreadLayer* threadLayer, bool isForked);
	virtual ~CommentLayer();
public: /* ThreadLayerからのコールバック関数 */
	virtual void appendComment(item::CommentPipeLine* const pipeLine, meta::Thread::Iterator const begin, meta::Thread::Iterator const end) = 0;
public:
	virtual void draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos) = 0;
};

}}

#endif /* COMMENTLAYER_H_ */
