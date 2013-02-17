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
#include "RawSprite.h"
#include "../util/ClassAccessor.h"
namespace saccubus {
namespace draw {

class CommentFactory {
private:
	DEF_ATTR_ACCESSOR(protected, private, Renderer*, renderer);
protected:
	logging::Logger& log;
public:
	CommentFactory(logging::Logger& log, Renderer* renderer);
	virtual ~CommentFactory();
public:
	virtual Sprite::Handler<Sprite> renderCommentText(std::shared_ptr<saccubus::draw::Context> ctx, const layer::item::Comment* comment) = 0;
	virtual saccubus::draw::Sprite::Handler<saccubus::draw::Sprite> renderLabelText(std::shared_ptr<saccubus::draw::Context> ctx, const saccubus::layer::item::Label* label) = 0;
};

}}
