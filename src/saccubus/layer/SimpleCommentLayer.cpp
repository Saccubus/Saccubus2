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

#include "SimpleCommentLayer.h"

namespace saccubus {
namespace layer {

SimpleCommentLayer::SimpleCommentLayer(logging::Logger& log, draw::Renderer* renderer, ThreadLayer* threadLayer, bool isForked)
:CommentLayer(log, renderer, threadLayer, isForked)
{
	// TODO Auto-generated constructor stub

}

SimpleCommentLayer::~SimpleCommentLayer() {
	// TODO Auto-generated destructor stub
}

void SimpleCommentLayer::appendComment(item::CommentPipeLine* const pipeLine, meta::Thread::Iterator const begin, meta::Thread::Iterator const end)
{

}

void SimpleCommentLayer::draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos)
{

}
void SimpleCommentLayer::onClick(int x, int y)
{

}


}}
