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

namespace saccubus {
namespace layer {

class CommentLayer: public saccubus::layer::Layer {
private:
	std::deque<context::Comment*> comments;
public:
	CommentLayer(logging::Logger& log, draw::Renderer* renderer);
	virtual ~CommentLayer();
public:
	virtual void draw(float vpos);
};

}}

#endif /* COMMENTLAYER_H_ */
